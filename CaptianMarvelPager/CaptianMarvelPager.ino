#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "CustomCharacter.h"

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
  lcd.clear();

  lcd.createChar(1,star1);
  lcd.createChar(2,star2);
  lcd.createChar(3,star3);
  lcd.createChar(4,star4);
  lcd.createChar(5,star5);
  lcd.createChar(6,star6);
  lcd.createChar(7,star7);
  lcd.createChar(8,star8);
  

//  lcd.createChar(17,f7);
//  lcd.createChar(18,f8);
//  lcd.createChar(19,f9);
//  lcd.createChar(20,f10);
//  lcd.createChar(21,f11);
//  lcd.createChar(22,f12);
//  lcd.createChar(23,f13);
//  lcd.createChar(24,f14);
//  lcd.createChar(25,f15);

}

void loop() 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SENDING...");
  delay(4000);
  blinkingDots();
  blinkingDots();
  frame1();
  delay(2000);
  frame2();
  delay(10000);
  

}

void blinkingDots()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(".");
  delay(1000);
  lcd.clear();
  lcd.print(". .");
  delay(1000);
  lcd.clear();
  lcd.print(". . .");
  delay(1000);
}

void frame1()
{
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.write(1);
  lcd.setCursor(7,0);
  lcd.write(2);
  lcd.setCursor(8,0);
  lcd.write(3);
  lcd.setCursor(9,0);
  lcd.write(4);
  lcd.setCursor(6,1);
  lcd.write(5);
  lcd.setCursor(7,1);
  lcd.write(6);
  lcd.setCursor(8,1);
  lcd.write(7);
  lcd.setCursor(9,1);
  lcd.write(8); 
}

void frame2()
{
  lcd.createChar(1,f1);
  lcd.createChar(2,f2);
  lcd.createChar(3,f3);
  lcd.createChar(4,f4);
  lcd.createChar(5,f5);
  lcd.createChar(6,f6);
  delay(1000);
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.setCursor(1,0);
  lcd.write(2);
  lcd.setCursor(2,0);
  lcd.write(3);
  lcd.setCursor(3,0);
  lcd.write(4);
  lcd.setCursor(4,0);
  lcd.write(5);
  lcd.setCursor(5,0);
  lcd.write(6);
  delay(1000);
  lcd.createChar(1,star1);
  lcd.createChar(2,star2);
  lcd.createChar(3,star3);
  lcd.createChar(4,star4);
  delay(1000);
  lcd.setCursor(6,0);
  lcd.write(1);
  lcd.setCursor(7,0);
  lcd.write(2); 
  lcd.setCursor(8,0);
  lcd.write(3);
  lcd.setCursor(9,0);
  lcd.write(4);
//  lcd.setCursor(10,0);
//  lcd.write(17);
//  lcd.setCursor(11,0);
//  lcd.write(18);
//  lcd.setCursor(12,0);
//  lcd.write(19);
//  lcd.setCursor(13,0);
//  lcd.write(20);
//  lcd.setCursor(14,0);
//  lcd.write(21);
//  lcd.setCursor(15,0);
//  lcd.write(22); 
  
//  lcd.setCursor(0,1);
//  lcd.write(23);
//  lcd.setCursor(1,1);
//  lcd.write(23);
//  lcd.setCursor(2,1);
//  lcd.write(23);
//  lcd.setCursor(3,1);
//  lcd.write(23);
//  lcd.setCursor(4,1);
//  lcd.write(23);
//  lcd.setCursor(5,1);
//  lcd.write(24);
//  lcd.setCursor(6,1);
  delay(1000);
  lcd.createChar(5,star5);
  lcd.createChar(6,star6);
  lcd.createChar(7,star7);
  lcd.createChar(8,star8);
  delay(1000);
  lcd.write(5);
  lcd.setCursor(7,1);
  lcd.write(6); 
  lcd.setCursor(8,1);
  lcd.write(7);
  lcd.setCursor(9,1);
  lcd.write(8);
//  lcd.setCursor(10,1);
//  lcd.write(25);
//  lcd.setCursor(11,1);
//  lcd.write(23);
//  lcd.setCursor(12,1);
//  lcd.write(23);
//  lcd.setCursor(13,1);
//  lcd.write(23);
//  lcd.setCursor(14,1);
//  lcd.write(23);
//  lcd.setCursor(15,1);
//  lcd.write(23); 
}

