// Define the pins
const int rainSensorPin = A1;     // analog Pin connected to the rain sensor
const int motorForwardPin = 9;    // Pin connected to the motor for forward rotation
const int motorReversePin = 8;    // Pin connected to the motor for reverse rotation

// Variables to track the state of the sensor and motor
bool previousSensorState = LOW;   // Stores the previous state of the sensor

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);

  // Ensure motor is off at the start
  digitalWrite(motorForwardPin, LOW);
  digitalWrite(motorReversePin, LOW);

  Serial.println("System initialized. Motor is OFF.");
}

void loop() {
  int analogValue = analogRead(rainSensorPin);           // Read the analog value of the rain sensor
  int currentSensorState = (analogValue < 500) ? HIGH : LOW;  // Inverted logic: LOW = no rain, HIGH = rain detected

  Serial.print("Analog Reading (A1): ");
  Serial.print(analogValue);
  Serial.print(" | Sensor State (Inverted): ");
  Serial.println(currentSensorState);

  if (currentSensorState == HIGH && previousSensorState == LOW) {
    Serial.println("Rain detected! Running motor forward...");
    
    digitalWrite(motorForwardPin, HIGH);    // Turn motor forward
    delay(7000);                            // Run motor forward for 2 seconds
    digitalWrite(motorForwardPin, LOW);     // Stop the motor

    Serial.println("Motor forward stopped.");
  } 
  else if (currentSensorState == LOW && previousSensorState == HIGH) {
    Serial.println("Rain stopped! Running motor in reverse...");
    
    digitalWrite(motorReversePin, HIGH);    // Turn motor in reverse
    delay(7000);                            // Run motor in reverse for 2 seconds
    digitalWrite(motorReversePin, LOW);     // Stop the motor

    Serial.println("Motor reverse stopped.");
  }

  // Update the previous sensor state
  previousSensorState = currentSensorState;

  delay(100);  // Add a small delay for stable serial output
}
