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
| [Ultrasonic Distance Sensor (HC-SR04)](https://www.sparkfun.com/products/15569) | Uses sonar to determine the distance to an object. This sensor reads from 2cm to 400cm (0.8inch to 157inch) with an accuracy of 0.3cm (0.1inches) |  |
| [Piezo Buzzer](https://arduinogetstarted.com/tutorials/arduino-piezo-buzzer) | Conneting to a positive charge will generate a constant tone |  |

<br>

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Feather Huzzah driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads)
- [MQTT Explorer](http://mqtt-explorer.com/)
- [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- [InfluxDB](https://www.influxdata.com/)
- [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/)
- [Grafana](https://grafana.com/)
- [Adafruit.io](https://io.adafruit.com/)

<br>

## Method

### Board Setup

1. The Feather Huzzah requires some additional setup when using it with the Arduino IDE. Visit the Adafruit site and [**download the SL driver**](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) in order to add via the Board Manager. Once connected, [**add the ESP8266WiFi library**](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html) to make it easier to connect your board to the internet.
2. Next add the [**PubSubClient library**](https://pubsubclient.knolleary.net/) to enable simple publish/subscribe messaging with a server that supports MQTT. There are a handful of example sketches here that may be helpful to work through.
3. A **very** important note: you will be using sensitive information in your sketch once you connect to your Wifi and MQTT server. **DO NOT share these in your code**-- create a separate header file that is included in your main sketch. When uploading to Github, add it to a ```.gitignore``` file.
```
// Wifi and MQTT
#include "arduino_secrets.h"

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;
```
4. Now we're ready to add our sensors. Follow the schematic below:
![Project schematic](/assets/plantMonitor_schematic.png)
5. Run two test scripts ```testMoisture.ino``` and ```testTempHum.ino``` to see whether the sensors are working correctly. The environmental variable values are printed to both the ```console.log``` and serial plotter. 
6. You will need to **calibrate** the nail moisture sensor to your unique environemnt because soil depth, distance between the nails, and angle of incidence will all affect the quality of your readings. One way to prevent this is to create a mount or use a clip to keep the nails in place. [**This design**](https://github.com/ucl-casa-ce/casa0014/tree/main/plantMonitor/enclosure) was created by [**drvkmr**](https://github.com/drvkmr). I also marked the nails with a sharpie to ensure the soil depth was the same every time.

<p align="center">
  <img src="/assets/completedSensor.jpg">
</p>

7. Next set up the Raspberry Pi as a gateway-- if it's a new board run the Raspberry Pi imager and get your specific network set up. [**This tutorial**](https://www.tomshardware.com/reviews/raspberry-pi-headless-setup-how-to,6028.html) was very helpful.


## Results
- Show screenshots
### Data Visualization
- MQTT Setup
- Raspberry Pi Gateway
- InfluxDB
- Grafana

### Challenges
- moisture sensor calibration and design flaws
- moisture sensor calibration necessary
- constant power needed for system, needed to disconnect to move to my home environment 

### Next Steps
- greener energy consumption
- make a closed loop system
- add watering/other passive sensors?
- integrate disturb counter sensor 

## Resources
Based on prior work:
- [plantMonitor](https://github.com/ucl-casa-ce/casa0014/tree/main/plantMonitor) designed by [@djdunc](https://github.com/djdunc)
- [Moisture detection with two nails](https://www.instructables.com/Moisture-Detection-With-Two-Nails/) designed by [Ronnie Tucker](https://www.instructables.com/member/ronnietucker/)
