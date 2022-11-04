# 🌱 plantMonitor
Plant monitor system using a WiFi development board, environmental sensors, and live data visualization 

## Overview
![Project Cover Photo](/assets/plantMonitor_Cover.jpg)

The goal of this project was to research the care requirements of a specific houseplant and build a system that would effectively monitor and report soil and environmental changes over time.

### The Plant
My plant was an **Aglaonema Red Star**, or **Chinese Evergreen**. Because of its red leaves it is **particularly sensitive to direct light**, significant temperature changes, and overwatering. Some additional care specifications include:
<br>
- Temperature range from 15C - 25C
- Water 2x a week, waiting until top soil dries out
- Fertilize once a month 

### Hardware 
|     |     |     |
| --- | --- | --- |
| _***Item***_ | _***Description***_ | _***Inputs / Outputs***_ |
| [Adafruit Feather HUZZAH ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview) | All-in-one' ESP8266 WiFi development board with built in USB and battery charging | [Pinout diagram](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/pinouts) |
| [Arduino Uno](https://store.arduino.cc/products/arduino-uno-rev3) | Microcontroller board based on the ATmega328P, a great starter board for offline projects | [Pinout diagram](https://www.circuito.io/blog/arduino-uno-pinout/) |
| [Huzzah Shield Board](https://github.com/ucl-casa-ce/casa0014/blob/main/plantMonitor/assets/PCB.png) | Designed at CASA specifically for plantMonitor project |  |
| [DHT22 Sensor](https://www.adafruit.com/product/385) | A capacitive humidity sensor and a thermistor to measure surrounding air | - takes readings every 2 seconds <br> - digital signal on the data pin (no analog input pins needed)
| Two steel nails | Sending +5V through the soil and measuring changes in resistance from one nail to another ([electrolysis](https://chem.libretexts.org/Bookshelves/Analytical_Chemistry/Supplemental_Modules_(Analytical_Chemistry)/Electrochemistry/Electrolytic_Cells/Electrolysis#:~:text=In%20Electrolysis%2C%20an%20electric%20current,and%20the%20chloro%2Dalkali%20process.)) |
| xxx | xxx | xxx |

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- Adafruit.io
- InfluxDB
- Telegraf
- [Grafana](https://grafana.com/)

## Method
![Project schematic](/assets/plantMonitor_schematic.png)
![Final Design](/assets/plantMonitor_FinalDesign.png)

### Data Visualization
- MQTT Setup
- Raspberry Pi Gateway
- InfluxDB
- Grafana


## Results
- Show screenshots

## Challenges
- moisture sensor calibration and design flaws
- moisture sensor calibration necessary
- constant power needed for system, needed to disconnect to move to my home environment 

## Next Steps
- greener energy consumption
- make a closed loop system
- add watering/other passive sensors?
- integrate disturb counter sensor 

## Resources
Based on prior work:
- [plantMonitor](https://github.com/ucl-casa-ce/casa0014/tree/main/plantMonitor) designed by [@djdunc](https://github.com/djdunc)
- [Moisture detection with two nails](https://www.instructables.com/Moisture-Detection-With-Two-Nails/) designed by [Ronnie Tucker](https://www.instructables.com/member/ronnietucker/)
