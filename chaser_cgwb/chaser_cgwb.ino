#include <Wire.h>                // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>   // Include I2C LCD library

// Pin definitions for the 4 LEDs
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5

// Delay time between each LED chase step (in milliseconds)
#define CHASE_DELAY 200

// Initialize the I2C LCD with address 0x27 and 16x2 size
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to control the LEDs
void controlLED(int led, bool state) {
  digitalWrite(led, state ? HIGH : LOW);  // Set the LED state
}

// Function to run LED chase in forward direction
void ledChaseForward() {
  controlLED(LED1, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED1, LOW);

  controlLED(LED2, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED2, LOW);

  controlLED(LED3, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED3, LOW);

  controlLED(LED4, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED4, LOW);
}

// Function to run LED chase in reverse direction
void ledChaseReverse() {
  controlLED(LED4, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED4, LOW);

  controlLED(LED3, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED3, LOW);

  controlLED(LED2, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED2, LOW);

  controlLED(LED1, HIGH);
  delay(CHASE_DELAY);
  controlLED(LED1, LOW);
}

void setup() {
  // Initialize the I2C LCD
  lcd.init();
  lcd.backlight();  // Turn on the LCD backlight
  
  // Display startup message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("LED Chase Pattern");
  lcd.setCursor(0, 1);
  lcd.print("Running...");

  // Set the LED pins as OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Ensure all LEDs are off at the start
  controlLED(LED1, LOW);
  controlLED(LED2, LOW);
  controlLED(LED3, LOW);
  controlLED(LED4, LOW);
}

void loop() {
  // Run the LED chase forward
  ledChaseForward();

  // Run the LED chase in reverse for a back-and-forth effect
  ledChaseReverse();
}
