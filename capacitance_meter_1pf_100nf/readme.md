# Capacitance Meter Using Arduino and I2C LCD

This project is a capacitance meter built using an Arduino, an I2C LCD module, and various components. The meter can measure capacitance in the picoFarad (pF), nanoFarad (nF), and microFarad (uF) ranges and display the measured capacitance on an LCD.

## Components Required

- Arduino (e.g., Uno, Nano, etc.)
- I2C LCD module (16x2 display)
- Capacitors for testing (1 pF - 1000 uF)
- Resistors
- Breadboard and jumper wires

## Pin Configuration

- **I2C LCD Pins:**
  - `GND`: Ground
  - `VCC`: 5V
  - `SDA`: A4 (Arduino Uno)
  - `SCL`: A5 (Arduino Uno)
  
- **Capacitance Meter Pins:**
  - `Cap_Pico_Pin` (Pin 9): To select PicoFarad mode
  - `Cap_UF_Pin` (Pin 10): To select MicroFarad mode
  - `Cap_Out_Pin` (Analog Pin A2): Output for capacitance measurement
  - `Cap_In_Pin` (Analog Pin A0): Input for capacitance measurement

## Circuit Diagram

Ensure that you connect all the components as per the following diagram:

- I2C LCD: Connect the `SDA` and `SCL` lines to Arduino pins `A4` and `A5` respectively.
- Capacitors: Connect the capacitors to the designated output and input pins (`A2` and `A0`) to measure their capacitance.

## How It Works

1. **PicoFarad Mode:**
   - If the `Cap_Pico_Pin` is pressed, the meter will measure the capacitance in the PicoFarad (pF) range.
   - The capacitance is calculated based on the discharge time of the capacitor.

2. **MicroFarad Mode:**
   - If the `Cap_UF_Pin` is pressed, the meter will switch to the MicroFarad (uF) range.
   - The measurement is performed by timing the charge cycle of the capacitor.

3. **Capacitance Calculation:**
   - In both modes, the Arduino calculates the capacitance based on the discharge or charge timing and the known values of resistors and other components.
   - The result is displayed on the I2C LCD with appropriate units (pF, nF, uF).

## Setup

1. Install the required libraries in the Arduino IDE:
   - `LiquidCrystal_I2C` for handling the I2C LCD.
   - `Wire` library (usually comes pre-installed with Arduino IDE).

2. Open the code file in the Arduino IDE and upload it to your board.

3. Connect the hardware as per the pin configuration and run the code. The LCD will display the measured capacitance.

## Installation of Libraries

1. Open Arduino IDE.
2. Navigate to `Sketch -> Include Library -> Manage Libraries...`.
3. Search for and install the `LiquidCrystal_I2C` library.
4. Ensure the `Wire` library is available (it's usually pre-installed with the IDE).

## Usage

- Power the Arduino and select the desired range (pF or uF) using the respective buttons connected to `Cap_Pico_Pin` and `Cap_UF_Pin`.
- The capacitance value will be shown on the I2C LCD.
- You can monitor the output via the Serial Monitor (9600 baud rate) for debugging purposes.

## Troubleshooting

- **LCD Not Displaying Text:** Double-check the I2C address (`0x27` or `0x3F`) and wiring (SDA, SCL).
- **Incorrect Capacitance Values:** Ensure proper calibration of the stray capacitance value in the code (`Stray_Cap`).
- **Intermittent Readings:** Use appropriate debounce techniques for button presses or ensure a stable power supply.

## License

This project is open-source and can be used or modified under the [MIT License](LICENSE).


