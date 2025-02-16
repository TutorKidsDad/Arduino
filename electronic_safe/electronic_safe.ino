#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Servo.h>

// Define constants for servo positions and delays
#define LOCKED_POS 50
#define UNLOCKED_POS 150
#define BUTTON_DELAY 250
#define SAVE_DELAY 30000
#define DISPLAY_DELAY 200
#define MAX_FAILED_ATTEMPTS 3

// Define pins for buttons
#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3
#define BUTTON_PIN_3 4
#define BUTTON_PIN_4 5
#define ENTER_BUTTON 10
#define CLEAR_LOCK_BUTTON 13

// Define EEPROM and other variables
int address = 0;
char CODE[10] = "1234E";
char inputStr[10];
char codeLength = 4;
int pos = 0;
bool unlocked = false;
unsigned long saveTimer = 0;
unsigned long displayTimer = 0;
int failedAttempts = 0;

// Setup I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo instance
Servo lockServo;

void setup() {
  // Initialize servo and set locked position
  lockServo.attach(A1);
  lockServo.write(LOCKED_POS);
  
  // Initialize buttons
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(CLEAR_LOCK_BUTTON, INPUT_PULLUP);

  // Initialize I2C LCD
  lcd.init();
  lcd.backlight();
  
  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");

  // Read EEPROM-stored code
  if (loadCodeFromEEPROM()) {
    lcd.setCursor(0, 1);
    lcd.print("Code Loaded");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Invalid EEPROM");
  }
  delay(2000);
  lcd.clear();
}

void loop() {
  checkButtons();
  updateDisplay();
  if (unlocked && digitalRead(CLEAR_LOCK_BUTTON) == LOW) {
    lock();
    delay(2000);
  }
}

void checkButtons() {
  // Check if buttons are pressed and update input string
  if (digitalRead(BUTTON_PIN_1) == LOW) { addCharToInput('1'); }
  else if (digitalRead(BUTTON_PIN_2) == LOW) { addCharToInput('2'); }
  else if (digitalRead(BUTTON_PIN_3) == LOW) { addCharToInput('3'); }
  else if (digitalRead(BUTTON_PIN_4) == LOW) { addCharToInput('4'); }
  else if (digitalRead(ENTER_BUTTON) == LOW) { validateCode(); }
}

void addCharToInput(char c) {
  inputStr[pos++] = c;
  inputStr[pos] = '\0';  // Null-terminate
  delay(BUTTON_DELAY);
}

void validateCode() {
  inputStr[pos++] = 'E';  // End character
  inputStr[pos] = '\0';   // Null-terminate
  delay(BUTTON_DELAY);

  if (strcmp(inputStr, CODE) == 0) {
    unlock();
  } else {
    failedAttempts++;
    lcd.clear();
    lcd.print("Access Denied");
    delay(2000);
    lcd.clear();
    lcd.print("Enter Password:");
    if (failedAttempts >= MAX_FAILED_ATTEMPTS) {
      lock();
      failedAttempts = 0;
    }
  }
  clearInput();
}

void updateDisplay() {
  if (millis() - displayTimer > DISPLAY_DELAY) {
    displayTimer = millis();
    lcd.setCursor(9, 0);
    lcd.print(inputStr);
  }
}

void clearInput() {
  pos = 0;
  inputStr[0] = '\0';
}

void unlock() {
  lockServo.write(UNLOCKED_POS);
  unlocked = true;
  lcd.clear();
  lcd.print("Access Granted");
  delay(2000);
}

void lock() {
  lockServo.write(LOCKED_POS);
  unlocked = false;
  lcd.clear();
  lcd.print("Locked");
}

bool loadCodeFromEEPROM() {
  // Load stored code from EEPROM
  for (int i = 0; i < codeLength + 1; i++) {
    CODE[i] = EEPROM.read(i);
    if (!isdigit(CODE[i]) && CODE[i] != 'E') return false;
  }
  CODE[codeLength + 1] = '\0';  // Null-terminate the string
  return true;
}
