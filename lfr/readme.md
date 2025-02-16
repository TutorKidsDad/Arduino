# Line-Following Robot

## Overview
This project is an **Arduino-based line-following robot** that uses two **IR sensors** to detect a black line on a white surface and controls **two DC motors** to follow the line.

## Features
- Uses **IR sensors** for line detection.
- Controls **DC motors** via an **H-Bridge motor driver**.
- Implements **line-following logic** to move forward, turn left, turn right, and stop.
- Adjustable **motor speed** using PWM.
- Improved **non-blocking code** for better responsiveness.

## Components Required
| Component         | Quantity |
|------------------|----------|
| Arduino Board (Uno/Nano/Mega) | 1 |
| IR Sensor Module | 2 |
| L298N Motor Driver Module | 1 |
| DC Motors | 2 |
| Wheels | 2 |
| Chassis | 1 |
| Battery Pack (9V or 12V) | 1 |
| Connecting Wires | As needed |

## Circuit Connections
| Arduino Pin | Component |
|------------|------------|
| A0 | Left IR Sensor |
| A1 | Right IR Sensor |
| 8 | Left Motor Forward (IN1) |
| 9 | Left Motor Backward (IN2) |
| 11 | Right Motor Forward (IN3) |
| 12 | Right Motor Backward (IN4) |
| 10 | Left Motor Speed (PWM) |
| 13 | Right Motor Speed (PWM) |

## How It Works
1. **IR Sensors** detect the line:
   - `0` (black) → Robot follows the line.
   - `1` (white) → Robot adjusts direction.
2. **Motor control logic**:
   - Both sensors detect black → Move forward.
   - Left sensor black, right sensor white → Turn left.
   - Left sensor white, right sensor black → Turn right.
   - Both sensors white → Stop.
3. The **robot continuously adjusts** its movement to stay on the line.

## Installation & Usage
### **Step 1: Upload the Code**
1. Install the **Arduino IDE**.
2. Connect your Arduino to the computer via USB.
3. Upload the provided sketch.

### **Step 2: Assemble the Circuit**
1. Connect the **IR sensors** to **A0** and **A1**.
2. Connect the **motor driver** to the motors and Arduino.
3. Power the system using a **battery pack**.

### **Step 3: Test the Robot**
1. Place the robot on a track with a **black line on a white surface**.
2. Observe its movement and adjust if necessary.

## Customization
- **Adjust Speed**: Change the `MOTOR_SPEED` variable in the code.
- **Smooth Turns**: Modify `turnLeft()` and `turnRight()` functions.
- **Add Obstacle Detection**: Integrate an **ultrasonic sensor**.
- **Wireless Control**: Implement **Bluetooth or WiFi** features.

## Troubleshooting
- **Robot not moving?**
  - Check motor driver wiring and battery voltage.
- **Not following the line properly?**
  - Adjust sensor placement and sensitivity.
- **Erratic movement?**
  - Ensure the track has a high-contrast black line.

## License
This project is open-source under the **MIT License**. Feel free to modify and share!



