const int LEFT_SENSOR = A0;
const int RIGHT_SENSOR = A1;
const int MOTOR_LEFT_FORWARD = 8;
const int MOTOR_LEFT_BACKWARD = 9;
const int MOTOR_RIGHT_FORWARD = 11;
const int MOTOR_RIGHT_BACKWARD = 12;
const int ENABLE_LEFT = 10;
const int ENABLE_RIGHT = 13;
const int MOTOR_SPEED = 200; // Adjustable speed (0-255)

void setup() {
  Serial.begin(115200);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT); 
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(ENABLE_RIGHT, OUTPUT);

  analogWrite(ENABLE_LEFT, MOTOR_SPEED);
  analogWrite(ENABLE_RIGHT, MOTOR_SPEED);

  stopMotors();
  Serial.println("Setup complete. Robot is ready.");
}

void loop() {
  static unsigned long lastTime = 0;
  const int interval = 100;

  if (millis() - lastTime >= interval) {
    lastTime = millis();
    readSensorsAndControlMotors();
  }
}

void readSensorsAndControlMotors() {
  int leftSensorValue = digitalRead(LEFT_SENSOR);  
  int rightSensorValue = digitalRead(RIGHT_SENSOR); 

  Serial.print("Left Sensor: ");
  Serial.print(leftSensorValue == 1 ? "Black" : "White");
  Serial.print(", Right Sensor: ");
  Serial.println(rightSensorValue == 1 ? "Black" : "White");

  if (leftSensorValue == 0 && rightSensorValue == 0) {
    Serial.println("Moving Forward");
    moveForward();
  } else if (leftSensorValue == 0 && rightSensorValue == 1) {
    Serial.println("Turning Left");
    turnLeft();
  } else if (leftSensorValue == 1 && rightSensorValue == 0) {
    Serial.println("Turning Right");
    turnRight();
  } else {
    Serial.println("Stopping");
    stopMotors();
  }
}

void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void turnLeft() {
  analogWrite(ENABLE_LEFT, 100);
  analogWrite(ENABLE_RIGHT, MOTOR_SPEED);
}

void turnRight() {
  analogWrite(ENABLE_LEFT, MOTOR_SPEED);
  analogWrite(ENABLE_RIGHT, 100);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}
