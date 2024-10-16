#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
volatile unsigned long microseconds;
volatile float capacitance;

int CapPf=9;
int CapUf=10;

const int Cap_Out = A2;
const int Cap_In = A0;
const float Stray_Cap = 24.48;
const float Cap_GND  = Stray_Cap;
const float Pullup_Res = 34.8;  
const int ADC_Value = 1023;

void setup() {
  lcd.begin(16, 2);
  pinMode(2,INPUT);
  
  pinMode(CapPf,INPUT);
  pinMode(CapUf,INPUT);
  
  pinMode(Cap_Out, OUTPUT);
  pinMode(Cap_In, OUTPUT);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("  Capacitance  ");
  lcd.setCursor(0,1);
  lcd.print("     Meter     ");
  delay(2000);
    
}
void cap() {
  microseconds=micros()-microseconds;  
  capacitance=1.443*microseconds/300;
  capacitance = capacitance/1000;
  Serial.print(capacitance,3);
  Serial.println("uF");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Range:   1uf-1mF");
  lcd.setCursor(0, 1);
  lcd.print(capacitance,3);
  lcd.print("uF          ");
  microseconds=micros();
  
  }
void loop(){
if(digitalRead(CapUf))
{
  attachInterrupt(0,cap,RISING);
}
if(digitalRead(CapPf))
{
  lcd.clear();
  pinMode(Cap_In, INPUT);
    digitalWrite(Cap_Out, HIGH);
    int val = analogRead(Cap_In);
    digitalWrite(Cap_Out, LOW);

    if (val < 1000)
    {
      pinMode(Cap_In, OUTPUT);

      float capacitance = (float)val * Cap_GND / (float)(ADC_Value - 

val);

      lcd.setCursor(0,0);
      lcd.print("Range:   1pF-1nF");
      lcd.setCursor(0,1);
      lcd.print(capacitance,3);
      lcd.setCursor(14,1);
      lcd.print("pF");
      delay(200);
    }
    
    else
    {
      pinMode(Cap_In, OUTPUT);
      delay(1);
      pinMode(Cap_Out, INPUT_PULLUP);
      unsigned long u1 = micros();
      unsigned long t;
      int digVal;

      do
      {
        digVal = digitalRead(Cap_Out);
        unsigned long u2 = micros();
        t = u2 > u1 ? u2 - u1 : u1 - u2;
      } 
      
      while ((digVal < 1) && (t < 400000L));

      pinMode(Cap_Out, INPUT);  
      val = analogRead(Cap_Out);
      digitalWrite(Cap_In, HIGH);
      int dischargeTime = (int)(t / 1000L) * 5;
      delay(dischargeTime);   
      pinMode(Cap_Out, OUTPUT);  
      digitalWrite(Cap_Out, LOW);
      digitalWrite(Cap_In, LOW);

      float capacitance = -(float)t / Pullup_Res / log(1.0 - (float)val / (float)ADC_Value);

      lcd.setCursor(0,0);
      lcd.print("Scale:   1pF-1nF");
      
      if (capacitance > 1000.0)
      {
        lcd.setCursor(0,1);
        lcd.print(capacitance / 1000.0, 2);
        lcd.setCursor(14,1);
        lcd.print("uF ");
        delay(200);
      }
        
      else
      {
        lcd.setCursor(0,1);
        lcd.print(capacitance);
        lcd.setCursor(14,1);
        lcd.print("nF");
        delay(200);
      }
  }
    while (micros() % 1000 != 0);
  }
  
}
