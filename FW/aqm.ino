#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>

#define EPD_CS    1
#define EPD_DC    27
#define EPD_RST   28
#define EPD_BUSY  26
#define AGS_SDA   6
#define AGS_SCL   7
#define BAT_PIN   29
#define LED_R     17
#define LED_G     16
#define LED_B     25

#define DISPLAY_INTERVAL_MS  60000UL
#define LOW_BAT_V            3.5f
#define LOW_BAT_FLASH_MS     100U
#define ADC_REF_V            3.3f
#define ADC_RES              4095.0f
#define BAT_DIVIDER          2.0f

#define AGS10_ADDR      0x1A
#define AGS10_REG_TVOC  0x00
#define AGS10_STATUS_OK 0x00
#define AGS10_WARMING   0x01

GxEPD2_BW<GxEPD2_266_GDEY0266T90, GxEPD2_266_GDEY0266T90::HEIGHT> display(
  GxEPD2_266_GDEY0266T90(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)
);

float         batV          = 0;
bool          lowBat        = false;
uint32_t      tvocPpb       = 0;
bool          warming        = true;
unsigned long lastDisplayMs = 0;

void ledOff() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
}

void flashLed(bool r, bool g, bool b, uint16_t ms) {
  digitalWrite(LED_R, r ? LOW : HIGH);
  digitalWrite(LED_G, g ? LOW : HIGH);
  digitalWrite(LED_B, b ? LOW : HIGH);
  delay(ms);
  ledOff();
}

float readBatV() {
  uint32_t sum = 0;
  for (int i = 0; i < 8; i++) {
    sum += analogRead(BAT_PIN);
    delay(2);
  }
  return (sum / 8.0f / ADC_RES) * ADC_REF_V * BAT_DIVIDER;
}


uint8_t crc8(const uint8_t* data, uint8_t len) {
  uint8_t crc = 0xFF;
  for (uint8_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (uint8_t b = 0; b < 8; b++) {
      crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
    }
  }
  return crc;
}


bool readAgs10() {
  Wire.beginTransmission(AGS10_ADDR);
  Wire.write(AGS10_REG_TVOC);
  if (Wire.endTransmission(false) != 0) return false;

  if (Wire.requestFrom(AGS10_ADDR, (uint8_t)5) != 5) return false;

  uint8_t buf[5];
  for (int i = 0; i < 5; i++) buf[i] = Wire.read();

  if (crc8(buf, 4) != buf[4]) return false;

  warming  = (buf[0] == AGS10_WARMING);
  tvocPpb  = ((uint32_t)buf[1] << 16) | ((uint32_t)buf[2] << 8) | buf[3];

  return true;
}

const char* tvocLabel(uint32_t ppb) {
  if (ppb <= 220)  return "Excellent";
  if (ppb <= 660)  return "Good";
  if (ppb <= 1430) return "Moderate";
  if (ppb <= 2200) return "Poor";
  return "Very poor";
}

void updateDisplay() {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setTextWrap(false);

    display.setFont(&FreeSans9pt7b);

  
    display.setCursor(4, 14);
    display.print(batV, 2);
    display.print("V");
    if (lowBat) {
      display.setCursor(50, 14);
      display.print(" LOW");
    }

 
    if (warming) {
      display.setCursor(display.width() - 76, 14);
      display.print("Warming up");
    }

    display.drawLine(0, 20, display.width(), 20, GxEPD_BLACK);

 
    display.setFont(&FreeSansBold18pt7b);
    char tvocStr[12];
    if (warming) {
      snprintf(tvocStr, sizeof(tvocStr), "---");
    } else {
      snprintf(tvocStr, sizeof(tvocStr), "%lu", tvocPpb);
    }
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(tvocStr, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((display.width() - w) / 2, 72);
    display.print(tvocStr);


    display.setFont(&FreeSans9pt7b);
    display.getTextBounds("ppb", 0, 0, &x1, &y1, &w, &h);
    display.setCursor((display.width() - w) / 2, 92);
    display.print("ppb");

    display.drawLine(0, 100, display.width(), 100, GxEPD_BLACK);


    const char* label = warming ? "Warming up..." : tvocLabel(tvocPpb);
    display.getTextBounds(label, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((display.width() - w) / 2, 130);
    display.print(label);

  } while (display.nextPage());

  display.powerOff();
}

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  ledOff();
  analogReadResolution(12);

  Wire.setSDA(AGS_SDA);
  Wire.setSCL(AGS_SCL);
  Wire.begin();

  display.init(0);
  display.setRotation(1);


  Wire.beginTransmission(AGS10_ADDR);
  if (Wire.endTransmission() != 0) {
    while (true) { flashLed(true, false, false, 300); delay(300); }
  }

  flashLed(false, true, false, 200);
}

void loop() {
  unsigned long now = millis();

  if (now - lastDisplayMs >= DISPLAY_INTERVAL_MS) {
    if (!readAgs10()) {
      flashLed(true, false, false, 100);
    }

    batV   = readBatV();
    lowBat = batV < LOW_BAT_V;
    if (lowBat) flashLed(false, false, true, LOW_BAT_FLASH_MS);

    updateDisplay();
    lastDisplayMs = now;
  }
}
