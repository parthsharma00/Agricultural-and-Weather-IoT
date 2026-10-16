# Agricultural & Weather IoT

Five small Arduino builds for sensing the world outside: a mini weather station, a soil-moisture monitor that tells you when to water, a GPS readout, a digital compass with a scrolling heading tape, and light-activated lighting. I built them while learning embedded systems. Each one taught me a different sensor protocol (I²C, UART/NMEA, analog), and together they cover most of what you'd need for a backyard farm or a field-deployable weather node.

> 📸 _Build photos coming soon_ <!-- add docs/*.jpg of each build -->

## Projects

| Project | What it does | Key hardware | What I learned |
|---|---|---|---|
| [`miniweatherstation/`](miniweatherstation) | Live temperature, barometric pressure and estimated altitude on a 20×4 LCD, refreshed every 2 s | BMP280 (I²C), 20×4 I²C LCD | Driving two I²C devices on one bus, unit conversion (Pa → hPa, pressure → altitude) |
| [`plantwatermoisture/`](plantwatermoisture) | Checks soil moisture every 12 hours and shows **DRY / OK / WET** with a "water now" prompt on an OLED | Capacitive/resistive soil probe, SH1106 128×64 OLED | Powering the probe only during a reading to stop electrode corrosion; threshold calibration |
| [`gps/`](gps) | Shows latitude and longitude to 5 decimal places, or the satellite count while it's still searching for a fix | NEO-6M-style GPS (UART), 16×2 LCD | Parsing NMEA sentences with TinyGPS++ over SoftwareSerial |
| [`compass/`](compass) | Digital compass with a sliding "horizon tape" (N/NE/E…), a custom needle glyph and a 3-digit heading | QMC5883L magnetometer, 16×2 LCD | Azimuth normalisation, mapping heading to a scrolling character window, custom LCD characters |
| [`LDR/`](LDR) | Switches a bank of 11 LEDs on when it gets dark and off when it's light | LDR module, LEDs | Digital threshold sensing, driving many outputs from an array |

Wiring diagrams for the GPS and compass builds are included as PDFs in their folders.

## Tech stack

Arduino (C++) · I²C · UART · Adafruit BMP280 · TinyGPS++ · QMC5883LCompass · LiquidCrystal_I2C · U8g2

## Running a project

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) (2.x).
2. Install the libraries the sketch uses via **Tools → Manage Libraries**:
   - Weather station: `Adafruit BMP280`, `LiquidCrystal I2C`
   - Soil moisture: `U8g2`
   - GPS: `TinyGPSPlus`, `LiquidCrystal I2C`
   - Compass: `QMC5883LCompass`, `LiquidCrystal I2C`
3. Wire the sensor using the PDF (where included) or the pin numbers at the top of each sketch.
4. Open the `.ino`, select your board (tested on Arduino Uno/Nano) and port, then click **Upload**.

> If your LCD stays blank, try address `0x3F` instead of `0x27`. If the BMP280 reports "Sensor Error!", try `0x77` instead of `0x76`.

## What's next

- Combine the weather station and soil sensor into one ESP32 node that logs to the cloud
- Add humidity (DHT22/BME280) and rainfall sensing
- Solar + deep-sleep power budget for a field-deployable version

## Related

- [Smart-Home-Automation-Library](https://github.com/parthsharma00/Smart-Home-Automation-Library): indoor safety and automation builds
- [Robotics-and-Human-Interface-IoT](https://github.com/parthsharma00/Robotics-and-Human-Interface-IoT): robotics, LoRa, and computer-vision HCI

## Author

**Parth Sharma**, Computer Science & Design at the Singapore University of Technology and Design (SUTD)
[GitHub](https://github.com/parthsharma00) · [LinkedIn](https://www.linkedin.com/in/parth-sharmasutd) · parthsharma72007@gmail.com
