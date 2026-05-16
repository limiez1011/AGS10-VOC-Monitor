[air quality monitor-bom.csv](https://github.com/user-attachments/files/27851702/air.quality.monitor-bom.csv)
# AGS10-VOC-Monitor
Battery-powered indoor air quality monitor that reads VOC every 60 seconds and displays it on an e-ink screen.

## Functionality
It uses an AGS10 TVOC sensor which samples the air every 60 seconds, when it's not sampling it goes into a sleep mode where the resistive heater turns off, the PCB includes an MCP73831 which charges LiPo batteries at 0.5A which is perfect for a 500mAh or 800mAh LiPo (1C/0.625C charge rate) The MCU is the seeed studios RP2040 which has a trace going from BATT+ to an ADC pin with a voltage divider so that we can know when to charge the batteries. The sample is then displayed on a 2.66in E-ink which is also updated every 60 seconds, It displays voltage and ppb.

## Bill of Materials
### (2 PCBS)
|Name                       |Purpose              |Quantity|Total Cost (USD)|Link                                                                                                                                                             |Distributor|
|---------------------------|---------------------|--------|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------|
|Passives                   |Caps,Resistors,Diodes|22      |1.00            |                                                                                                                                                                 |JLCPCB     |
|MICROCHIP MCP73831T-2ATI/OT|lipo charger         |2       |2.40            |                                                                                                                                                                 |JLCPCB     |
|AGS10                      |VOC sensor           |2       |3.20            |                                                                                                                                                                 |JLCPCB     |
|SEEED rp2040               |MCU                  |2       |11.30           |[link](https://www.tme.eu/ro/details/seeed-102010428/kituri-de-dezvoltare-altele/seeed-studio/xiao-rp2040/)                                                              |TME EU     |
|PCB                        |PCBA                 |5       |17.00           |                                                                                                                                                                 |JLCPCB     |
|Waveshare 18321            |eink display         |1       |14.28           |[link](https://www.tme.eu/ro/details/wsh-18321/hartie-electronica/waveshare/18321/?brutto=1&currency=RON&utm_content=&campaign_id=10591401989&gad_campaignid=10591401989)|TME EU     |


## Photos
<img width="2050" height="956" alt="image" src="https://github.com/user-attachments/assets/4af562a3-5cb1-4b01-9b93-99927ffcaabc" />
<img width="1901" height="923" alt="image" src="https://github.com/user-attachments/assets/e25fbd65-b662-4ea6-8552-4feafca930a6" />


