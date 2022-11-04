# 🌱 plantMonitor 🌱
Monitor system using a WiFi development board, environmental sensors, and live data visualization 

## Overview
<p align="center">
  <img src="/assets/aglaonema red star.jpg">
</p>

The goal of this project was to research the care requirements of a specific houseplant and build a system that would effectively monitor and report soil and environmental changes over time.

### The Plant
My plant is an **Aglaonema Red Star**, or **Chinese Evergreen**. Because of its red leaves it is **particularly sensitive to direct light**, significant temperature changes, and overwatering. Some additional care specifications include:
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
| Ultrasonic Distance Sensor (HC-SR04) | xxx | xxx |
| Passive Buzzer | xxx | xxx |

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Feather Huzzah driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
- [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- [InfluxDB](https://www.influxdata.com/)
- [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/)
- [Grafana](https://grafana.com/)
- [Adafruit.io](https://io.adafruit.com/)

## Method
![Project schematic](/assets/plantMonitor_schematic.png)
<p align="center">https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html#7</p>
<br>
The Feather Huzzah requires some additional setup when using it with the Arduino IDE. Visit the Adafruit site and [download](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide) the driver in order to add via the Board Manager. <br>
Once connected, the next step is to connect the board to the internet using your local connection. 

<p align="center">
  <img src="/assets/plantMonitor_FinalDesign.jpg">
</p>


## Results
- Show screenshots
### Data Visualization
- MQTT Setup
- Raspberry Pi Gateway
- InfluxDB
- Grafana

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
