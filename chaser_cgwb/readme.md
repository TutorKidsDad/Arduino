# LED Chase Pattern with I2C LCD Display

This project demonstrates an LED chase pattern using four LEDs connected to an Arduino. The pattern is displayed on an I2C LCD, showing a message while the LEDs chase in a forward and reverse sequence.

## Components Required

- Arduino (Uno, Nano, etc.)
- 4 LEDs
- 4 Resistors (220Ω or 330Ω)
- Breadboard and jumper wires
- I2C LCD (16x2)
- I2C LCD module (address: 0x27)
- I2C LCD library (`LiquidCrystal_I2C`)

## Pin Configuration

### LEDs:
- **LED1**: Pin 2
- **LED2**: Pin 3
- **LED3**: Pin 4
- **LED4**: Pin 5

### I2C LCD:
- **SDA**: A4 (Arduino Uno)
- **SCL**: A5 (Arduino Uno)
- **GND**: Ground
- **VCC**: 5V

## Circuit Diagram

Ensure the following connections:
- LEDs: Connect each LED to the respective pins (2, 3, 4, 5) with resistors in series.
- I2C LCD: Connect `SDA` to A4, `SCL` to A5, `GND` to ground, and `VCC` to 5V.

## How It Works

1. **LED Chase Pattern:**
   - Four LEDs are connected to the Arduino.
   - The LEDs turn on and off in a chase pattern, first in the forward direction and then in reverse.

2. **I2C LCD Display:**
   - The I2C LCD displays a startup message `"LED Chase Pattern Running..."`.
   - The LCD remains active throughout the chase pattern execution.

## Setup

1. **Install the required libraries:**
   - Open Arduino IDE and navigate to `Sketch -> Include Library -> Manage Libraries...`.
   - Search for `LiquidCrystal_I2C` and install it.
   - Ensure the `Wire` library is available (it's pre-installed with Arduino IDE).

2. **Connect the hardware as per the circuit diagram.**

3. **Upload the Code:**
   - Open the `.ino` code file in Arduino IDE and upload it to your Arduino board.
   - The LCD will display a message, and the LEDs will start chasing in a forward and reverse pattern.

