#include <AFMotor.h>

#define TRIG 9
#define ECHO 10

AF_DCMotor motor1(1);   // M1
AF_DCMotor motor2(2);   // M2

long duration;
int distance;

void setup() {

  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance < 20) {

    Serial.println("Object detected - Moving Backward");

    motor1.run(BACKWARD);
    motor2.run(BACKWARD);

  }
  else {

    Serial.println("Path Clear - Stop");

    motor1.run(RELEASE);
    motor2.run(RELEASE);

  }

  delay(200);
}
