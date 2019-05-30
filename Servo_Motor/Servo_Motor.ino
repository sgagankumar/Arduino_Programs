// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 5; 
int i;
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){ 
//   // Make servo go to 0 degrees 
//   Servo1.write(0); 
//   delay(2000); 
//   // Make servo go to 90 degrees 
//   Servo1.write(90); 
//   delay(2000); 
//   // Make servo go to 180 degrees 
//   Servo1.write(180); 
//   delay(2000);
   for(i=0; i<90; i++)
   {
    Servo1.write(i);
    delay(50);
   } 
   delay(6000);
   for(i=90; i>0; i--)
   {
    Servo1.write(i);
    delay(50);
   }
   delay(6000);
}
