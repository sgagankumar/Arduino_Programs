#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //because it is a wire package we use predefined PINS const
  Wire.begin(D2,D3);          
  //Wire.begin(sda,scl)
  lcd.init(); 
  lcd.begin(16,2);
  lcd.backlight();
}

void loop() {

  // put your main code here, to run repeatedly:
  lcd.clear();

  int a,b,c;
  a=10;
  b=20;
  c=3000;
  lcd.setCursor(0,0);
  lcd.print("DATE:");
  lcd.setCursor(6,0);
  lcd.print(a);
  lcd.setCursor(8,0);
  lcd.print("/");
  lcd.setCursor(9,0);
  lcd.print(b);
  lcd.setCursor(11,0);
  lcd.print("/");
  lcd.setCursor(12,0);
  lcd.print(c);

  lcd.setCursor(0,1);
  lcd.print("TIME:");
  lcd.setCursor(6,1);
  lcd.print(a);
  lcd.setCursor(8,1);
  lcd.print(":");
  lcd.setCursor(9,1);
  lcd.print(b);
  
  delay(5000);

}
