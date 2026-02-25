// MQ-135 Air Quality Monitor

const int mq135Pin = A0;
const int redLed = 12;
const int greenLed = 11;
const int buzzer = 10;

// Adjust this threshold after testing
int moderateThreshold = 350;
int poorThreshold = 500;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  Serial.println("MQ-135 Air Quality Monitor");
  delay(2000); // Sensor warm-up time (basic)
}

void loop() {

  int airQuality = analogRead(mq135Pin);

  Serial.print("Air Quality Value: ");
  Serial.print(airQuality);

  // GOOD AIR
  if (airQuality < moderateThreshold) {
    Serial.println("  |  Status: GOOD 😊");
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    noTone(buzzer);
  }

  // MODERATE AIR
  else if (airQuality >= moderateThreshold && airQuality < poorThreshold) {
    Serial.println("  |  Status: MODERATE 😐");
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);
  }

  // POOR AIR
  else {
    Serial.println("  |  Status: POOR 🚨");
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    tone(buzzer, 1500);
  }

  delay(1000);
}
