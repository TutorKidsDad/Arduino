# Arduino DS18B20 Temperature Sensor Reading

This project reads temperature data from one or more DS18B20 temperature sensors using the OneWire protocol and displays the results on the Serial Monitor. The code is designed to handle multiple sensors connected to a single data pin and prints both Celsius and Fahrenheit temperatures for each sensor.

## Features

- **Multi-sensor support**: Automatically detects and reads temperature from multiple DS18B20 sensors on the OneWire bus.
- **Non-blocking delay**: The code uses a non-blocking delay mechanism (`millis()`) to allow further functionality without halting the program.
- **Error handling**: Checks for valid temperature data, detecting ghost devices or malfunctioning sensors.
- **Address printing**: Each sensor's unique address is printed in hexadecimal format.

## Hardware Required

- Arduino (Uno, Mega, or compatible)
- DS18B20 temperature sensor(s)
- 4.7kΩ pull-up resistor
- Jumper wires
- Breadboard

## Connections

| DS18B20 Pin  | Arduino Pin       |
|--------------|-------------------|
| GND          | GND               |
| VCC          | 5V (or 3.3V)      |
| DQ (Data)    | Pin 4             |

You also need to add a 4.7kΩ pull-up resistor between the **DQ** (data) pin and the **VCC** pin.

## Libraries Used

- [OneWire Library](https://www.arduino.cc/reference/en/libraries/onewire/)
- [DallasTemperature Library](https://www.arduino.cc/reference/en/libraries/dallastemperature/)

Make sure to install these libraries using the Arduino Library Manager before uploading the code.

## Installation

1. Clone this repository or download the project as a ZIP file and extract it.
2. Open the `.ino` file in the Arduino IDE.
3. Connect your DS18B20 sensor(s) to your Arduino as per the connections above.
4. Upload the code to your Arduino board.
5. Open the Serial Monitor at 115200 baud to view the temperature readings.

## Code Overview

### Setup

In the `setup()` function, the OneWire bus is initialized, and the code searches for any DS18B20 sensors connected. If sensors are found, their unique addresses are printed.

### Loop

In the `loop()` function, every 5 seconds (or a configurable time), the code requests the temperature data from all connected sensors. It checks for valid data before printing the temperature in both Celsius and Fahrenheit.

### Key Functions

- **sensors.requestTemperatures()**: Sends a command to all connected sensors to retrieve the latest temperature data.
- **sensors.getTempC()**: Retrieves the temperature in Celsius for a given sensor address.
- **DallasTemperature::toFahrenheit()**: Converts Celsius to Fahrenheit.

### Address Printing

The function `printAddress()` prints the unique 64-bit address of each connected sensor in hexadecimal format.

## Example Output

```plaintext
Locating devices... Found 2 devices.
Found device 0 with address: 28FF1A2C6416024E
Found device 1 with address: 28FF0B3C4617034E

Temperature for device 0: Temp C: 25.12 °C, Temp F: 77.22 °F
Temperature for device 1: Temp C: 24.87 °C, Temp F: 76.77 °F

