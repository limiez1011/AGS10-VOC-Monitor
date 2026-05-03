# AGS10-VOC-Monitor
Battery-powered indoor air quality monitor that reads VOC every 60 seconds and displays it on an e-ink screen.

## Functionality
It uses an AGS10 TVOC sensor which samples the air every 60 seconds, when it's not sampling it goes into a sleep mode where the resistive heater turns off, the PCB includes an MCP73831 which charges LiPo batteries at 0.5A which is perfect for a 500mAh or 800mAh LiPo (1C/0.625C charge rate) The MCU is the seeed studios RP2040 which has a trace going from BATT+ to an ADC pin with a voltage divider so that we can know when to charge the batteries. The sample is then displayed on a 2.66in E-ink which is also updated every 60 seconds, It displays voltage and ppb.

## Bill of Materials
### (Per PCB)
1x - Seeed studios RP2040
1x - AGS10 TVOC sensor
1x - MCP73831 LiPo charge IC
1x - 0402 100nF cap
2x - 0603 4.7uF cap
1x - 0603 Red LED
1x - SOD-123 Schottky diode
2x - 0402 4.7K R
1x - 0402 2k R
2x - 0402 100K R

## Photos
<img width="2050" height="956" alt="image" src="https://github.com/user-attachments/assets/4af562a3-5cb1-4b01-9b93-99927ffcaabc" />
<img width="1901" height="923" alt="image" src="https://github.com/user-attachments/assets/e25fbd65-b662-4ea6-8552-4feafca930a6" />


