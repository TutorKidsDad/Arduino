// Motor driver pin definitions
int mr1 = 8;   // Motor Right Forward
int mr2 = 9;   // Motor Right Backward
int ml1 = 10;  // Motor Left Forward
int ml2 = 11;  // Motor Left Backward

// IR sensor pin definitions
int sr = 6;    // Right IR sensor input
int sl = 7;    // Left IR sensor input

// Motor speed control pins (PWM)
int enr = 3;   // Enable pin for Right Motor
int enl = 5;   // Enable pin for Left Motor

// Speed and timing variables
int vspeed = 150;  // Speed for forward motion (0-255)
int tspeed = 200;  // Speed for turning (higher for sharp turns)
int tdelay = 100;  // Delay for turning (in milliseconds)

// Sensor state variables
int svr = 0;   // Sensor Right Value (0 = Black, 1 = White)
int svl = 0;   // Sensor Left Value (0 = Black, 1 = White)

// LED pin for status/debugging
int led = 13;  // Built-in LED for status

// Setup function runs once when the program starts
void setup() {
  // Set motor control pins as OUTPUT
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);

  // Set sensor pins as INPUT
  pinMode(sr, INPUT);
  pinMode(sl, INPUT);

  // Set LED pin as OUTPUT
  pinMode(led, OUTPUT);

  // Indicate system is starting (blink LED)
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(5000);  // Delay for system setup or sensor calibration
}

// Main loop runs continuously
void loop() {
  // Read sensor values (LOW = Black, HIGH = White)
  svr = digitalRead(sr);
  svl = digitalRead(sl);

  // Movement logic based on sensor values
  if (svl == LOW && svr == LOW) {
    forward();  // Both sensors on black - move forward
  } else if (svl == HIGH && svr == LOW) {
    left();     // Left sensor on white, right on black - turn left
  } else if (svl == LOW && svr == HIGH) {
    right();    // Left sensor on black, right on white - turn right
  } else if (svl == HIGH && svr == HIGH) {
    stop();     // Both sensors on white - stop
  }
}

// Function to move forward
void forward() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, vspeed);  // Set right motor speed
  analogWrite(enl, vspeed);  // Set left motor speed
}

// Function to move backward (not used in this code)
void backward() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, vspeed);
  analogWrite(enl, vspeed);
}

// Function to turn right
void right() {
  digitalWrite(mr1, LOW);    // Stop right motor
  digitalWrite(mr2, HIGH);   // Right motor moves backward
  digitalWrite(ml1, HIGH);   // Left motor moves forward
  digitalWrite(ml2, LOW);
  analogWrite(enr, tspeed);  // Set turning speed for right motor
  analogWrite(enl, tspeed);  // Set turning speed for left motor
  delay(tdelay);             // Wait for turn to complete
}

// Function to turn left
void left() {
  digitalWrite(mr1, HIGH);   // Right motor moves forward
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);    // Stop left motor
  digitalWrite(ml2, HIGH);   // Left motor moves backward
  analogWrite(enr, tspeed);  // Set turning speed for right motor
  analogWrite(enl, tspeed);  // Set turning speed for left motor
  delay(tdelay);             // Wait for turn to complete
}

// Function to stop all motion
void stop() {
  analogWrite(enr, 0);       // Stop right motor
  analogWrite(enl, 0);       // Stop left motor
}
