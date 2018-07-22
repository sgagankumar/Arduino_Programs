#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //because it is a wire package we use predefined PINS const
  Wire.begin(0,2);         
  //Wire.begin(sda,scl)
  
  lcd.begin();
  
  lcd.home();

  lcd.print("tequed labs");

  lcd
}

void loop() {
  // put your main code here, to run repeatedly:

}
