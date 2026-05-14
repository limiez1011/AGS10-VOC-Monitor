# AGS10-VOC-Monitor
Battery-powered indoor air quality monitor that reads VOC every 60 seconds and displays it on an e-ink screen.

## Functionality
It uses an AGS10 TVOC sensor which samples the air every 60 seconds, when it's not sampling it goes into a sleep mode where the resistive heater turns off, the PCB includes an MCP73831 which charges LiPo batteries at 0.5A which is perfect for a 500mAh or 800mAh LiPo (1C/0.625C charge rate) The MCU is the seeed studios RP2040 which has a trace going from BATT+ to an ADC pin with a voltage divider so that we can know when to charge the batteries. The sample is then displayed on a 2.66in E-ink which is also updated every 60 seconds, It displays voltage and ppb.

## Bill of Materials
### (Per PCB)
| QTY | Part | Supplier | Price |
| --- | --- | --- | --- |
| 1 | WAVESHARE 18321 | TME EU | 14.28 USD |
| 1 | Seeed studios RP2040 | TME EU | 5.65 USD |
| 1 | AGS10 TVOC sensor | JLCPCB | 1.60 USD |
| 1 | 0402 100nF cap | JLCPCB | 0.01 USD |
| 2 | 0603 4.7uF cap | JLCPCB | 0.11 USD |
| 1 | 0603 Red LED | JLCPCB | 0.01 USD |
| 1 | 0402 470 R | JLCPCB | 0.08 USD |
| 1 | MICROCHIP MCP73831T-2ATI/OT | JLCPCB | 1.2 USD |
| 1 | SOD-123 Schottky diode | JLCPCB | 0.024 USD |
| 2 | 0402 4.7K R | JLCPCB | 0.02 USD |
| 1 | 0402 2k R | JLCPCB | 0.01 USD |
| 2 | 0402 100K R | JLCPCB | 0.02 |
| --- | --- | --- | --- |
| TOTAL |
| 24 USD (w/o mfg fees)
| SHIPPING |
| TME EU- 6.73 USD  (ESTIMATED) | JLCPCB - 11.24 USD | TOTAL - 18 USD |
| GRAND TOTAL |
| 45 USD (all extra fees included) |
## Photos
<img width="2050" height="956" alt="image" src="https://github.com/user-attachments/assets/4af562a3-5cb1-4b01-9b93-99927ffcaabc" />
<img width="1901" height="923" alt="image" src="https://github.com/user-attachments/assets/e25fbd65-b662-4ea6-8552-4feafca930a6" />


