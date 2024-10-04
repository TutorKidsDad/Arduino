#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 4 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a OneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Create a DallasTemperature instance using the OneWire reference
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

void setup(void) {
  // Start serial communication at a baud rate of 115200
  Serial.begin(115200);
  
  // Initialize the DallasTemperature library
  sensors.begin();
  
  // Get the count of devices on the OneWire bus
  numberOfDevices = sensors.getDeviceCount();
  
  // Locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // Loop through each device, print out the device's address
  for (int i = 0; i < numberOfDevices; i++) {
    DeviceAddress tempDeviceAddress;
    // Search the wire for the device's address
    if (sensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.println(" but could not detect address. Check power and cabling.");
    }
  }
}

void loop(void) {
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  const long interval = 5000;  // 5 second interval

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    sensors.requestTemperatures(); // Send the command to get temperatures
    
    // Loop through each device, print out temperature data
    for (int i = 0; i < numberOfDevices; i++) {
      DeviceAddress tempDeviceAddress;
      // Search the wire for the device's address
      if (sensors.getAddress(tempDeviceAddress, i)) {
        // Output the device ID
        Serial.print("Temperature for device ");
        Serial.print(i);
        Serial.print(": ");
        
        float tempC = sensors.getTempC(tempDeviceAddress);
        
        // Check for valid temperature (-127 is usually a failure code)
        if (tempC != DEVICE_DISCONNECTED_C) {
          // Print the temperature in Celsius and Fahrenheit
          Serial.print("Temp C: ");
          Serial.print(tempC);
          Serial.print(" °C, Temp F: ");
          Serial.print(DallasTemperature::toFahrenheit(tempC));
          Serial.println(" °F");
        } else {
          Serial.println("Error: Could not read temperature data");
        }
      } else {
        Serial.println("Error: Could not retrieve address for this device.");
      }
    }
  }
}

// Function to print a device address in hexadecimal format
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
