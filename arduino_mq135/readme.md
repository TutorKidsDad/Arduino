
# MQ-135 Air Quality Monitor (Arduino)

## Overview

This project uses the MQ-135 sensor with Arduino to monitor air quality and detect gases like CO₂, NH₃, smoke, benzene, etc.

## Components Required

* Arduino Uno
* MQ-135 Sensor Module
* Breadboard
* Jumper wires
* 220Ω resistors
* Red & Green LEDs (optional)
* Buzzer (optional)

---

## Wiring Connections

| MQ-135 | Arduino                  |
| ------ | ------------------------ |
| VCC    | 5V                       |
| GND    | GND                      |
| A0     | A0                       |
| D0     | Optional (Digital Pin 2) |

### Optional Indicators

| Component | Arduino Pin |
| --------- | ----------- |
| Red LED   | 12          |
| Green LED | 11          |
| Buzzer    | 10          |

---

## ⚙️ Circuit Notes

* Arduino ADC range = 0–1023 (10-bit)
* Sensor output directly compatible with Arduino (5V logic)
* No voltage divider required

---

## Calibration

1. Burn-in time: 24–48 hours (first use)
2. Warm-up: 5–10 minutes
3. Observe clean air value in Serial Monitor
4. Set threshold accordingly

Typical clean air value: 150–300

---

## Reading Range

| Condition | Analog Value |
| --------- | ------------ |
| Clean Air | 150–300      |
| Moderate  | 300–500      |
| Poor      | 500+         |

---

## ⚠ Notes

* MQ-135 does not directly give ppm without calibration formula
* Sensitive to humidity & temperature
* Use averaging for stable readings

---

---

# 📁 README 2 — ESP8266 (NodeMCU) + MQ-135

---

# MQ-135 IoT Air Monitor (ESP8266)

## Overview

This project creates a WiFi-based air quality monitoring system using NodeMCU.

## Components Required

* NodeMCU ESP8266
* MQ-135 Sensor Module
* Breadboard
* Jumper wires

---

## Wiring Connections

| MQ-135 | NodeMCU      |
| ------ | ------------ |
| VCC    | VIN (5V)     |
| GND    | GND          |
| A0     | A0           |
| D0     | Not required |

---

## Important Voltage Note

NodeMCU A0 maximum input = **1V**

Most MQ-135 modules include voltage divider.

If not → you MUST add external voltage divider.

---

## Circuit Notes

* ESP8266 ADC range = 0–1023
* Only 1 analog pin available
* Suitable for IoT dashboard projects

---

## IoT Features

* Connect to WiFi
* Web dashboard
* Cloud integration possible (ThingSpeak, Blynk)

---

## Calibration

Typical values:

* Clean Air: 100–250
* Moderate: 250–400
* Poor: 400+

---

## Notes

* WiFi causes slight ADC noise
* Use averaging for stability
* Ensure stable 5V supply to sensor heater

---

---

# README 3 — ESP32 + MQ-135

---

# MQ-135 IoT Air Monitor (ESP32)

## Overview

ESP32-based smart air quality monitor with WiFi and advanced ADC resolution.

---

## Components Required

* ESP32 Dev Module
* MQ-135 Sensor Module
* Breadboard
* Jumper wires

---

## Wiring Connections

| MQ-135 | ESP32        |
| ------ | ------------ |
| VCC    | 5V           |
| GND    | GND          |
| A0     | GPIO34 (ADC) |
| D0     | Not required |

---

## ⚠ Important Voltage Warning

ESP32 ADC max input = **3.3V**

If MQ-135 outputs 5V → use voltage divider:

Example divider:

* 10kΩ resistor
* 20kΩ resistor

---

## ADC Details

* ESP32 ADC range = 0–4095 (12-bit)
* More accurate than Arduino/ESP8266
* Use `analogReadResolution(12);`

---

## Typical ESP32 Values

| Condition | ADC Value |
| --------- | --------- |
| Clean Air | 800–1500  |
| Moderate  | 1500–2500 |
| Poor      | 2500+     |

---

## IoT Capabilities

* Web server hosting
* MQTT support
* ThingSpeak integration
* Mobile app dashboards

---

## Calibration Steps

1. Burn-in 24–48 hours
2. Warm-up 5–10 minutes
3. Measure clean air average
4. Set thresholds 20–30% above baseline

---

## Notes

* ESP32 ADC is sensitive to noise
* Avoid using WiFi + ADC on same pin groups if unstable
* Use averaging for accuracy

---

# Common Technical Notes (All Boards)

✔ Sensor heater consumes ~150mA
✔ Works best at room temperature
✔ Humidity affects readings
✔ Use moving average filter for stable data
✔ Not industrial-grade certified

---

If you want, I can now:

* Combine all into a professional GitHub project structure
* Generate circuit diagrams for each board
* Add ppm calculation formula
* Create full project report (school / exhibition ready)
* Make a downloadable ZIP project structure

Tell me your next step 
