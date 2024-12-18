// Pin definitions
#define LEFT_SENSOR A0           // Left IR sensor input
#define RIGHT_SENSOR A1          // Right IR sensor input
#define MOTOR_LEFT_FORWARD 5     // Motor 1 IN1
#define MOTOR_LEFT_BACKWARD 6    // Motor 1 IN2
#define MOTOR_RIGHT_FORWARD 9    // Motor 2 IN3
#define MOTOR_RIGHT_BACKWARD 10  // Motor 2 IN4
#define ENABLE_LEFT 3            // Enable pin for Motor 1
#define ENABLE_RIGHT 11          // Enable pin for Motor 2

void setup() {
  // Start Serial communication for monitoring
  Serial.begin(115200);

  // IR sensor pins
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  // Motor control pins
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(ENABLE_RIGHT, OUTPUT);

  // Set motor speed to maximum at startup
  analogWrite(ENABLE_LEFT, 255);  // Max speed (0-255)
  analogWrite(ENABLE_RIGHT, 255); // Max speed (0-255)

  // Ensure motors are off at startup
  stopMotors();

  Serial.println("Setup complete. Robot is ready.");
}

void loop() {
  int leftSensorValue = digitalRead(LEFT_SENSOR);  // Read left sensor (0 = black, 1 = white)
  int rightSensorValue = digitalRead(RIGHT_SENSOR); // Read right sensor (0 = black, 1 = white)

  // Log sensor values to the Serial Monitor
  Serial.print("Left Sensor: ");
  Serial.print(leftSensorValue == 0 ? "Black" : "White");
  Serial.print(", Right Sensor: ");
  Serial.println(rightSensorValue == 0 ? "Black" : "White");

  // Logic for line following
  if (leftSensorValue == 0 && rightSensorValue == 0) {
    // Both sensors on black line - go straight
    Serial.println("Action: Moving Forward");
    moveForward();
  } else if (leftSensorValue == 0 && rightSensorValue == 1) {
    // Left sensor on black, right on white - turn left
    Serial.println("Action: Turning Left");
    turnLeft();
  } else if (leftSensorValue == 1 && rightSensorValue == 0) {
    // Left sensor on white, right on black - turn right
    Serial.println("Action: Turning Right");
    turnRight();
  } else {
    // Both sensors on white - stop
    Serial.println("Action: Stopping");
    stopMotors();
  }

  // Small delay for readability in Serial Monitor
  delay(100);
}

void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}
