# Vehicle Tracking System with GPS, Wi-Fi, and LCD

## Overview
This project is a **vehicle tracking system** using an **Arduino-compatible microcontroller** with **GPS**, **Wi-Fi**, and an **LCD display**. The system retrieves real-time GPS coordinates, connects to a Wi-Fi network, and serves a webpage displaying vehicle details and live location.

## Features
- **GPS Tracking:** Retrieves latitude and longitude from the GPS module.
- **Wi-Fi Connectivity:** Connects to a Wi-Fi network to host a webpage.
- **Webpage Display:** Shows vehicle details, including coordinates and a Google Maps link.
- **LCD Display:** Displays IP address, system status, and GPS data.

## Components Required
- **Microcontroller:** Arduino Uno or Mega
- **GPS Module:** NEO-6M or similar
- **Wi-Fi Module:** ESP8266 (using AT commands)
- **LCD Display:** I2C 16x2 LCD
- **Jumper Wires**

## Pin Connections
| Component  | Microcontroller Pins |
|------------|---------------------|
| **Wi-Fi TX**  | **Pin 2 (RX)** |
| **Wi-Fi RX**  | **Pin 3 (TX)** |
| **GPS TX**    | **Pin 10 (RX)** |
| **GPS RX**    | **Pin 11 (TX)** |
| **LCD SDA**   | **A4** |
| **LCD SCL**   | **A5** |

## Code Explanation
### 1. **Wi-Fi Connection**
- Sends AT commands to ESP8266.
- Connects to a predefined SSID and password.
- Retrieves the **IP address** and starts a web server on **port 80**.

### 2. **GPS Data Handling**
- Reads GPS data from the module.
- Extracts **latitude** and **longitude** from the NMEA sentence `$GPGGA`.
- Converts coordinates into decimal format.

### 3. **Webpage Generation**
- Constructs an HTML page with:
  - Vehicle information (Name, DOB, Vehicle No.)
  - **Current GPS Coordinates**
  - A clickable **Google Maps link**
- Sends the webpage to connected clients.

### 4. **LCD Display**
- Shows **Wi-Fi status** and **IP address**.
- Displays **real-time GPS coordinates**.

## Setup Instructions
1. **Upload the Code:**
   - Use Arduino IDE.
   - Select the correct board and COM port.
2. **Connect Hardware:**
   - Ensure GPS, Wi-Fi module, and LCD are properly wired.
3. **Power the Circuit:**
   - Use a 5V power source.
4. **Monitor Serial Output:**
   - Open the serial monitor to debug Wi-Fi and GPS status.
5. **Access the Webpage:**
   - Connect to the same Wi-Fi network as the ESP8266.
   - Enter the assigned IP address in a web browser.

## Webpage Example Output
```html
<h1>Welcome to Vehicle Tracking</h1>
<p>1. Name: John Doe</p>
<p>2. DOB: 12 Feb 1993</p>
<p>4. Vehicle No.: RJ05 XY 4201</p>
<p>Coordinates:</p>
<p>Latitude: 26.9124</p>
<p>Longitude: 75.7873</p>
<a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=26.9124+75.7873">
  Click Here for Google Maps
</a>
```

## Troubleshooting
- **No Wi-Fi Connection?**
  - Ensure the correct SSID and password in `AT+CWJAP="SSID","PASSWORD"`.
- **No GPS Data?**
  - Check the GPS module wiring and power supply.
  - Ensure it's placed in an open space for better satellite visibility.
- **Webpage Not Loading?**
  - Ensure the ESP8266 is correctly assigned an IP address.
  - Try restarting the system.

## Future Enhancements
- Add **GPRS support** for internet-based tracking.
- Implement **real-time updates** using WebSockets.
- Include **data logging** for tracking history.

## License
This project is open-source and available under the **MIT License**.


