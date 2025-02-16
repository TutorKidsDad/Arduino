#include <Wire.h>                // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>   // Include I2C LCD library

// Initialize the I2C LCD with address 0x27 and 16x2 size
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Global variables for capacitance measurement
volatile unsigned long microseconds;
volatile float capacitance;

// Pin Definitions
const int Cap_Pico_Pin = 9;
const int Cap_UF_Pin = 10;
const int Cap_Out_Pin = A2;
const int Cap_In_Pin = A0;

// Constants
const float Stray_Cap = 24.48;   // Stray Capacitance in pF
const float Cap_GND = Stray_Cap; // Ground Capacitance (could be adjusted)
const float Pullup_Res = 34.8;   // Pullup Resistor in kilo-ohms
const int ADC_Max_Value = 1023;  // Maximum ADC value

void setup() {
    // Initialize the I2C LCD
    lcd.init();
    lcd.backlight();  // Turn on the backlight
    
    // Pin configurations
    pinMode(2, INPUT);
    pinMode(Cap_Pico_Pin, INPUT_PULLUP);
    pinMode(Cap_UF_Pin, INPUT_PULLUP);
    pinMode(Cap_Out_Pin, OUTPUT);
    pinMode(Cap_In_Pin, OUTPUT);

    // Serial Monitor
    Serial.begin(9600);
    
    // Initial LCD display
    lcd.setCursor(0, 0);
    lcd.print("  Capacitance  ");
    lcd.setCursor(0, 1);
    lcd.print("     Meter     ");
    delay(2000);
}

void displayCapacitance(float value, const char* unit) {
    lcd.setCursor(0, 1);
    lcd.print(value, 3);
    lcd.setCursor(14, 1);
    lcd.print(unit);
}

void cap() {
    microseconds = micros() - microseconds;
    capacitance = 1.443 * microseconds / 300.0;  // Adjust calculation for accuracy
    capacitance /= 1000.0;  // Convert to uF

    // Output to serial and LCD
    Serial.print(capacitance, 3);
    Serial.println(" uF");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Range:   1uF-1mF");
    displayCapacitance(capacitance, "uF");

    microseconds = micros();
}

void measureCapacitance() {
    lcd.clear();
    
    // Pin settings for measurement
    pinMode(Cap_In_Pin, INPUT);
    digitalWrite(Cap_Out_Pin, HIGH);
    int adcValue = analogRead(Cap_In_Pin);
    digitalWrite(Cap_Out_Pin, LOW);

    if (adcValue < 1000) {
        // Pico/nano range capacitance
        pinMode(Cap_In_Pin, OUTPUT);
        float capacitance = (float)adcValue * Cap_GND / (ADC_Max_Value - adcValue);
        lcd.setCursor(0, 0);
        lcd.print("Range:   1pF-1nF");
        displayCapacitance(capacitance, "pF");
        delay(200);
    } else {
        // Micro range capacitance
        pinMode(Cap_In_Pin, OUTPUT);
        delay(1);
        pinMode(Cap_Out_Pin, INPUT_PULLUP);
        
        unsigned long t = measureTime();
        pinMode(Cap_Out_Pin, INPUT);
        adcValue = analogRead(Cap_Out_Pin);
        dischargeCapacitance(t, adcValue);
    }
}

unsigned long measureTime() {
    unsigned long startMicros = micros();
    unsigned long t = 0;
    int digitalValue;
    
    do {
        digitalValue = digitalRead(Cap_Out_Pin);
        unsigned long currentMicros = micros();
        t = currentMicros > startMicros ? currentMicros - startMicros : startMicros - currentMicros;
    } while ((digitalValue < 1) && (t < 400000L));

    return t;
}

void dischargeCapacitance(unsigned long t, int adcValue) {
    // Calculate capacitance based on discharge time
    float capacitance = -(float)t / Pullup_Res / log(1.0 - (float)adcValue / (float)ADC_Max_Value);
    
    lcd.setCursor(0, 0);
    lcd.print("Scale:   1pF-1nF");
    
    if (capacitance > 1000.0) {
        displayCapacitance(capacitance / 1000.0, "uF");
    } else {
        displayCapacitance(capacitance, "nF");
    }
    
    delay(200);
}

void loop() {
    // Interrupt-based capacitance measurement for uF range
    if (digitalRead(Cap_UF_Pin)) {
        attachInterrupt(digitalPinToInterrupt(2), cap, RISING);
    }
    
    // Measure capacitance for the pF range
    if (digitalRead(Cap_Pico_Pin)) {
        measureCapacitance();
    }
}
