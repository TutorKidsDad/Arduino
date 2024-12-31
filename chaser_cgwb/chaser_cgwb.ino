// Pin definitions for the 4 LEDs
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5

// Delay time between each LED chase step (in milliseconds)
#define CHASE_DELAY 200

void setup() {
  // Set the LED pins as OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Ensure all LEDs are off at the start
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void loop() {
  // Turn on LEDs one by one in a chase pattern
  digitalWrite(LED1, HIGH);  // Turn on LED1
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED1, LOW);   // Turn off LED1

  digitalWrite(LED2, HIGH);  // Turn on LED2
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED2, LOW);   // Turn off LED2

  digitalWrite(LED3, HIGH);  // Turn on LED3
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED3, LOW);   // Turn off LED3

  digitalWrite(LED4, HIGH);  // Turn on LED4
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED4, LOW);   // Turn off LED4

  // Optional: Reverse chase for a back-and-forth effect
  digitalWrite(LED4, HIGH);  // Turn on LED4
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED4, LOW);   // Turn off LED4

  digitalWrite(LED3, HIGH);  // Turn on LED3
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED3, LOW);   // Turn off LED3

  digitalWrite(LED2, HIGH);  // Turn on LED2
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED2, LOW);   // Turn off LED2

  digitalWrite(LED1, HIGH);  // Turn on LED1
  delay(CHASE_DELAY);        // Wait
  digitalWrite(LED1, LOW);   // Turn off LED1
}
