#include <LiquidCrystal_I2C.h>
#include<Wire.h>

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {

   Wire.begin(D6,D7);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(1,0);
  lcd.print("Drive Safe");
  lcd.setCursor(0, 1);
  lcd.print("Have A Good Day");
  delay(1000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Keep Calm");
  lcd.setCursor(0, 1);
  lcd.print("YAyyy");
  while(1)
  {
    Serial.print("Done");
  }
  
}
