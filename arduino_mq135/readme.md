
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

## Circuit Notes

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

## Notes

* MQ-135 does not directly give ppm without calibration formula
* Sensitive to humidity & temperature
* Use averaging for stable readings

---
