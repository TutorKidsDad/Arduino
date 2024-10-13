

#define TOUCH_ORIENTATION  1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 100
#define MAXPRESSURE 1000


//temp part
#include <SmoothThermistor.h>

SmoothThermistor smoothThermistor(A5);
//
//

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

//

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410

//switch part
int led=12;
//switch part



// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A1, YP = A2, YM = 7; //ID=0x9341
//Touch Pin Wiring XP=6 XM=A1 YP=A2 YM=7

//const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
//const int TS_LEFT=   740,  TS_RT=154,  TS_TOP=281,  TS_BOT=903;//opposite touch/

const int TS_LEFT=123,TS_RT=901,TS_TOP=119,TS_BOT=881;


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}


void setup(void)
{
    Serial.begin(9600);
   
    //switch part
       
        pinMode(led,OUTPUT);
    
    //
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);            //landscape
    tft.fillScreen(BLACK);
    on_btn.initButton(&tft,  80, 150, 90, 110, BLUE, GREY, BLACK, "ON", 2);
    off_btn.initButton(&tft, 240, 150, 90, 110, BLUE, GREY, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
   tft.setCursor(139, 140);
   tft.setTextColor(WHITE, RED);
   tft.setTextSize(2);
   tft.println("OFF");
    
}


void loop(void)
{


//

        float val=smoothThermistor.temperature();
//
     tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(2);
    tft.setCursor(100, 10);
    tft.print("TEMP");

    //
    tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3);
    tft.setCursor(130, 40);
    tft.print(val);

     tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(2);
    tft.setCursor(230, 50);
    tft.print("'C");
//    tft.setCursor(120, 40);
//    tft.print(val);
  
  //
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (off_btn.justReleased())
        off_btn.drawButton();
    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        digitalWrite(led,LOW);
   tft.setCursor(139, 140);
   tft.setTextColor(BLACK, GREEN);
   tft.setTextSize(2);
   tft.println("ON_");
 
       
    }
    if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        digitalWrite(led,HIGH);
    tft.setCursor(139, 140);
   tft.setTextColor(WHITE, RED);
   tft.setTextSize(2);
   tft.print("OFF");
    }
}
