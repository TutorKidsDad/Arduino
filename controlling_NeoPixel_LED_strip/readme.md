# NeoPixel LED Strip Control with Arduino

## Overview
This project demonstrates how to control an Adafruit NeoPixel LED strip using an Arduino. It includes various lighting effects such as color wipes, theater chase, and rainbow animations.

## Hardware Requirements
- Arduino (Uno, Mega, etc.)
- Adafruit NeoPixel LED Strip (WS2812, WS2812B, or compatible)
- 1000 µF capacitor (to prevent power surges)
- 300-500 Ohm resistor (to protect data line)
- External power supply (if required by the LED strip)
- Jumper wires

## Software Requirements
- Arduino IDE
- Adafruit NeoPixel library (install via Arduino Library Manager)

## Circuit Diagram
1. **NeoPixel Data Pin** → Connect to **Arduino PIN 6**
2. **NeoPixel Power (VCC)** → Connect to **5V (or external power)**
3. **NeoPixel Ground (GND)** → Connect to **Arduino GND**
4. **1000 µF Capacitor** → Across VCC and GND
5. **300-500 Ohm Resistor** → In series with the data pin

## Installation
1. Install the **Adafruit NeoPixel** library via the Arduino IDE Library Manager.
2. Copy and paste the provided code into the Arduino IDE.
3. Select the correct board and port in the Arduino IDE.
4. Upload the code to the Arduino.

## Code Explanation
- **`setup()`**: Initializes the NeoPixel strip and turns all LEDs off.
- **`loop()`**: Runs different LED animations continuously.
- **`colorWipe(color, delay)`**: Fills the strip one pixel at a time.
- **`rainbow(delay)`**: Displays a moving rainbow effect.
- **`rainbowCycle(delay)`**: Displays a full-spectrum rainbow cycle.
- **`theaterChase(color, delay)`**: Creates a theater-style lighting effect.
- **`theaterChaseRainbow(delay)`**: Combines theater chase with rainbow colors.
- **`Wheel(position)`**: Generates a color from a 255-step color wheel.

## Usage
After uploading the code, the LED strip will cycle through different animations, including:
- Red, Green, and Blue color wipes
- Theater chase in white, red, and blue
- Rainbow and rainbow cycle effects
- Theater chase with a rainbow effect

## Troubleshooting
- Ensure all connections are correct and secure.
- Use an external power supply if the Arduino cannot provide sufficient current.
- Check that the Adafruit NeoPixel library is installed correctly.

## License
This project is open-source and can be modified and distributed freely.

## References
- [Adafruit NeoPixel Guide](https://learn.adafruit.com/adafruit-neopixel-uberguide)


