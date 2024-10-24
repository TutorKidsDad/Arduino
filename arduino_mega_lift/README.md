
# Mini Elevator Project

This project simulates a simple multi-floor elevator system using an Arduino and various hardware components. The elevator can handle floor requests from inside the elevator or from each floor (for going up or down). It uses a stepper motor for movement, LEDs to indicate calls and directions, a seven-segment display to show the current floor, and a matrix to display directional arrows.

## Table of Contents
- [Introduction](#introduction)
- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Code Explanation](#code-explanation)
- [How to Use](#how-to-use)
- [Future Improvements](#future-improvements)

## Introduction
The Mini Elevator project demonstrates a multi-floor elevator system controlled by an Arduino. The system allows users to press up/down buttons at each floor and select floor buttons inside the elevator. The elevator moves to the requested floor and displays its current floor on a seven-segment display. It also shows directional arrows using an LED matrix.

## Components Required
- Arduino board (e.g., Arduino Uno or Mega)
- Stepper motor with a motor driver (e.g., 28BYJ-48 with ULN2003 driver)
- Seven-segment display
- LED matrix display
- Push buttons (for floor and up/down requests)
- LEDs (for indicating floor and up/down requests)
- Resistors (for LEDs and push buttons)
- Power supply
- Breadboard and jumper wires

## Circuit Diagram
**Note:** You'll need to connect the hardware components as specified in the code. The code defines the pins for the stepper motor, buttons, LEDs, seven-segment display, and matrix.

### Pin Setup
- **Stepper Motor**: Connected to pins `9, 10, 11, 12`
- **Up/Down Buttons**: Connected to pins `22, 23, 24, 25` (up) and `30, 31, 32, 33` (down)
- **Up/Down LEDs**: Connected to pins `26, 27, 28, 29` (up) and `34, 35, 36, 37` (down)
- **Floor Buttons**: Connected to pins `44, 45, 46, 47, 48`
- **Floor LEDs**: Connected to pins `49, 50, 51, 52, 53`
- **Seven-segment Display**: Connected to pins `2, 3, 4, 5, 6, 7, 8`
- **Matrix Display**: Connected to pins `39, 43, 41`

## Code Explanation
The project code is designed to control the elevator's behavior based on the floor and directional button presses. Here's an overview of the main sections:

1. **Initialization**: The `setup()` function initializes the motor, sets pin modes for buttons and LEDs, and reads persistent data from EEPROM. It also runs a self-test to ensure all components are working correctly.

2. **Self-Test Function**: This function tests all LEDs, buttons, and the display at startup.

3. **Main Loop**: The `loop()` function handles:
   - Checking for button presses and recording requests.
   - Managing motor movements and updating the current floor.
   - Indicating elevator status using the LED matrix and seven-segment display.

4. **Persistent Data Storage**: The elevator's current state and floor levels are saved in EEPROM for recovery after a power failure.

5. **Error Handling and Calibration Mode**: Calibration mode allows manual adjustments of floor positions. The code also ensures the elevator does not over-rotate and that the destination floor remains within valid limits.

## How to Use
1. **Hardware Setup**: Build the circuit as per the pin setup described above. Ensure all connections are secure.

2. **Code Upload**: Upload the provided code to your Arduino using the Arduino IDE.

3. **Calibration**: After powering on, enter calibration mode by pressing the first and last floor buttons simultaneously. This will allow you to adjust the motor’s step count for each floor. Save the calibration data by following the on-screen instructions.

4. **Operating the Elevator**: Use the floor and up/down buttons to request floors or move the elevator. The seven-segment display will show the current floor number, and the matrix will indicate the direction of movement.

## Future Improvements
- **Error Detection**: Implement checks to validate that `destinationFloor` remains within a valid range. Also, detect if the elevator gets stuck (e.g., motor steps not matching expected results) to improve reliability.
- **Speed Control**: Adjust the motor speed based on the distance between floors for smoother movement.
- **User Interface**: Add a simple LCD or OLED display to provide additional feedback to the user.
- **Over-rotation Protection**: Ensure the motor does not move beyond the highest or lowest floor by adding physical limit switches.

