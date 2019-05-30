#include <Servo.h>

int buzz = D0;
int sensor1 = D1;     //Left sensor 1
int sensor2 = D2;     //Left sensor 2
int sensor3 = D3;     //Car sensor
int sensor4 = D4;     //Right sensor 2
int sensor5 = D5;     //Right sensor 1
int rled = D6;
int gled = D7;
int gate = D8;

int buzzDelay = 9;
int gateDelay =50;

int value1=0,value2=0,value3=0,value4=0,value5=0,carPresent=0;
Servo Servo1;       //Servo Object
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value1 = digitalRead(sensor1);
  value5 = digitalRead(sensor5);
 // Serial.print(value1);
 // Serial.print(value5);
  Serial.println("Waiting for Train");
  Serial.println("/t/t/t/t/tLCD : AgriCloud : Automize your farm with Google Assitant for just Rs.10,000");
  while((value1==0)&&(value5==0))
  {
    Serial.print(". ");
    delay(1000);
    value1 = digitalRead(sensor1);
    value5 = digitalRead(sensor5);
  }
  if(value1)
  {
    Serial.println("Train is coming from LEFT");
    Serial.println("/t/t/t/t/tLCD : Train is approaching Stop Crossing");
    left();
  }
  else if(value5)
  {
    Serial.println("Train is coming from RIGHT");
    Serial.println("/t/t/t/t/tLCD : Train is approaching Stop Crossing");
    right();
  }
  delay(2000);
}

void left()
{
  Serial.print("Waiting for Sensor1 :");
  value1 = digitalRead(sensor1);
  while(value1==0)
  {
    Serial.print(". ");
    delay(1000);
    value1 = digitalRead(sensor1);
  }
  Serial.println("Train Passed Sensor 1");
  Serial.println("/t/t/t/t/tLCD : Closing gate Watch Out !!!!");
  closegate();
  
  Serial.println("Activating car detection");
  value3 =digitalRead(sensor3);
  if(value3==1)  
  {
    carPresent=1;
    digitalWrite(rled, HIGH);
    Serial.println("CAR STUCK WARNING.....!!!!!");
  }
  value2 = digitalRead(sensor2);
  while(value2==0)
  {
    Serial.print(". ");
    delay(1000);
    value2 = digitalRead(sensor2);
  }
  Serial.println("Train Passed Sensor 2");
  if(carPresent==0)
  {
    digitalWrite(gled, HIGH);
    Serial.println("Train is Safe to pass");
  }
  value5 = digitalRead(sensor5);
  while(value5==0)
  {
    Serial.print(". ");
    delay(1000);
    value5 = digitalRead(sensor5);
  }
  Serial.println("Train Passed Sensor 5");
  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);
  opengate();
  carPresent=0;
  Serial.println("Train Mechanism Reset");
  Serial.println("/t/t/t/t/tLCD : Congrats!! You were protected by SmartTrainCrossing ~A Product by TEAM CIPHER");
}

void right()
{
  Serial.print("Waiting for Sensor5 :");
  value5 = digitalRead(sensor5);
  while(value5==0)
  {
    Serial.print(". ");
    delay(1000);
    value5 = digitalRead(sensor5);
  }
  Serial.println("Train Passed Sensor 5");
  Serial.println("Closing gate");
  Serial.println("/t/t/t/t/tLCD : Closing gate Watch Out !!!!");
  closegate();
  
  Serial.println("Activating car detection");
  value3 =digitalRead(sensor3);
  if(value3==1)  
  {
    carPresent=1;
    digitalWrite(rled, HIGH);
    Serial.println("CAR STUCK WARNING.....!!!!!");
  }
  value4 = digitalRead(sensor4);
  while(value4==0)
  {
    Serial.print(". ");
    delay(1000);
    value4 = digitalRead(sensor4);
  }
  Serial.println("Train Passed Sensor 4");
  if(carPresent==0)
  {
    digitalWrite(gled, HIGH);
    Serial.println("Train is Safe to pass");
  }
  value1 = digitalRead(sensor1);
  while(value1==0)
  {
    Serial.print(". ");
    delay(1000);
    value1 = digitalRead(sensor1);
  }
  Serial.println("Train Passed Sensor 1");
  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);
  opengate();
  carPresent==0;
  Serial.println("Train Mechanism Reset"); 
  Serial.println("/t/t/t/t/tLCD : Congrats!! You were protected by SmartTrainCrossing ~A Product by TEAM CIPHER");
}

void closegate()
{
  int i;
  Servo1.attach(gate); 
   for(i=90; i>=0; i--)
   {
    Servo1.write(i);
    if(i%buzzDelay==0)
    {
      digitalWrite(buzz, HIGH);
      delay(gateDelay);
      digitalWrite(buzz,LOW);
    }
    else
    {
      delay(gateDelay);
    }
   }
  Servo1.detach();
}

void opengate()
{ 
  int i;
  Servo1.attach(gate); 
  for(i=0; i<90; i++)
   {
    Servo1.write(i);
    if(i%buzzDelay==0)
    {
      digitalWrite(buzz, HIGH);
      delay(gateDelay);
      digitalWrite(buzz,LOW);
    }
    else
    {
      delay(gateDelay);
    }
   } 
   Servo1.detach();
}

