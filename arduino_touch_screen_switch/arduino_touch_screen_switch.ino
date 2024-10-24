#define TOUCH_ORIENTATION  1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#include <SmoothThermistor.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

#define MINPRESSURE 100
#define MAXPRESSURE 1000

// TFT Colors
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410

// Touch and Button Config
const int XP = 6, XM = A1, YP = A2, YM = 7; // Touch Panel Pins
const int TS_LEFT = 123, TS_RT = 901, TS_TOP = 119, TS_BOT = 881;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Thermistor Config
SmoothThermistor smoothThermistor(A5);

// Button and LED Config
Adafruit_GFX_Button on_btn, off_btn;
const int ledPin = 12;
int pixel_x, pixel_y;

bool Touch_getXY(void) {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT); // restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);
    digitalWrite(XM, HIGH);
    
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width());
        pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

void drawTemperature(float temp) {
    tft.fillRect(130, 40, 80, 30, BLACK); // Clear previous temperature
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    tft.setCursor(130, 40);
    tft.print(temp, 1); // Display temperature with 1 decimal place

    tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(2);
    tft.setCursor(230, 50);
    tft.print("'C");
}

void setupButtons() {
    on_btn.initButton(&tft, 80, 150, 90, 110, BLUE, GREY, BLACK, "ON", 2);
    off_btn.initButton(&tft, 240, 150, 90, 110, BLUE, GREY, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
}

void setup(void) {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);

    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9486;
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
    
    setupButtons();
    drawStatus("OFF", RED);
}

void drawStatus(const char* status, uint16_t color) {
    tft.setCursor(139, 140);
    tft.setTextColor(WHITE, color);
    tft.setTextSize(2);
    tft.print(status);
}

void handleButtons() {
    bool pressed = Touch_getXY();
    on_btn.press(pressed && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(pressed && off_btn.contains(pixel_x, pixel_y));

    if (on_btn.justReleased()) on_btn.drawButton();
    if (off_btn.justReleased()) off_btn.drawButton();

    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        digitalWrite(ledPin, LOW);
        drawStatus("ON_", GREEN);
    }

    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        digitalWrite(ledPin, HIGH);
        drawStatus("OFF", RED);
    }
}

void loop(void) {
    static unsigned long lastTempUpdate = 0;
    const unsigned long updateInterval = 1000; // Update every 1 second

    if (millis() - lastTempUpdate >= updateInterval) {
        lastTempUpdate = millis();
        float temperature = smoothThermistor.temperature();
        drawTemperature(temperature);
    }

    handleButtons();
}
