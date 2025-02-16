# Password-Protected Lock System with I2C LCD and Servo Motor

This project implements a password-protected lock system using an I2C LCD display, buttons for input, a servo motor for locking/unlocking, and an EEPROM to store the password. The user can enter a password using buttons, and if the correct password is entered, the system unlocks the servo. The system can also update the password, which is stored in the EEPROM.

## Features
- **Password Protection:** The system allows users to input a password using buttons, and grants access if the correct password is entered.
- **EEPROM Storage:** The password is stored in EEPROM so that it persists after power loss.
- **Servo Lock/Unlock:** A servo motor simulates the locking mechanism, which moves between locked and unlocked positions.
- **I2C LCD Display:** A 16x2 I2C LCD display provides feedback to the user.
- **Debounced Button Inputs:** Ensures reliable input handling, reducing false triggering.
- **Failed Attempts Lockout:** After several failed password attempts, the system locks itself to prevent brute-force attacks.

## Components Required
- ESP32 or Arduino (or other microcontroller)
- I2C 16x2 LCD Display
- 4 Push Buttons (for password input)
- 1 Push Button (for 'Enter')
- 1 Push Button (for 'Clear Lock')
- Servo Motor
- EEPROM (if not already on board)
- Connecting Wires
- Breadboard (optional)

## Circuit Diagram
- **I2C LCD Connections:**
  - SDA (to ESP32 or Arduino SDA pin)
  - SCL (to ESP32 or Arduino SCL pin)
  - VCC and GND (to 5V and GND)

- **Button Connections:**
  - Four input buttons for `1`, `2`, `3`, `4` are connected to pins 2, 3, 4, and 5 respectively.
  - The 'Enter' button is connected to pin 10.
  - The 'Clear Lock' button is connected to pin 13.
  - Each button is connected to GND, with `INPUT_PULLUP` configuration in the code.

- **Servo Motor:**
  - Signal pin connected to pin `A1`
  - Power and ground connected to 5V and GND.

## Installation
1. Clone or download this repository to your local machine.
2. Open the project in the Arduino IDE (or your preferred IDE).
3. Install the following libraries using the Arduino Library Manager:
   - `LiquidCrystal_I2C`
   - `EEPROM` (if using an ESP32)
   - `Servo`
4. Connect the hardware as per the circuit diagram.
5. Upload the code to your ESP32 or Arduino.

## Usage Instructions
1. **Boot up the system**: When the system starts, it will display a welcome message on the LCD.
2. **Entering the Password**:
   - Use buttons `1`, `2`, `3`, `4` to input the correct password.
   - Press the 'Enter' button to submit your input.
3. **Correct Password**:
   - If the password matches, the servo will move to the unlocked position, and the LCD will display "Access Granted".
4. **Wrong Password**:
   - If the password is incorrect, the system will display "Access Denied".
   - After a few failed attempts, the system will lock out for a timeout period.
5. **Updating the Password**:
   - The password can be updated by entering a new code and storing it in EEPROM. This happens after unlocking successfully.

## Customizing the Password
- The default password is `1234`.
- To change the default password, modify the value of the `CODE` array in the source code, or update it via the EEPROM process described in the project.

