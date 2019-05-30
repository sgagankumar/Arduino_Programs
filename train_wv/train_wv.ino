//this is the program for the first IR(the 4 gates exept the car one)
#include<Servo.h>
#include <ESP8266WiFi.h>
        //D0 free
int ir1 = D1;
int ir2 = D2;
        //D6 free for LCD 
int ir4 = D3;
        //D7 is servo motor
int ir5 = D4;
int t1 = D6;
int t2 = D7;
        //D7 free for LCD
int op  = D8; //this sends the digital value 1 to the second mcu
        //buzzer A0 free (this can be used as a regular digital pin also)for buzzer
int pos=0;
String apiKey = "GVKY13RMI3LSHAK6";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "home";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
const char* server = "api.thingspeak.com";
int timeCounter=0;
int valIp;
Servo servo;
WiFiClient client;
void setup()
{
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(t1, OUTPUT);
  pinMode(t2, OUTPUT);
  pinMode(op, OUTPUT);
  servo.attach(D5);
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
   Serial.println("");
   Serial.println("WiFi connected");
 
}

void loop()
{
  
  Serial.println(valIp);
  delay(1000);
  //condition1 00

  digitalWrite(t1,LOW);
  digitalWrite(t2,LOW);
  Serial.println(LOW);
  Serial.println(HIGH);
  
  Serial.println("waiting for a train to come ");
  int ReadIr1 = digitalRead(ir1);
  int ReadIr2, ReadIr4, ReadIr5;
  ReadIr5 = digitalRead(ir5);
  
  
  if (ReadIr1 == 1 )
  {
        
        servo.write(0);
        ReadIr2 = digitalRead(ir2);
        Serial.println("IR1 is activated :train is coming");
        digitalWrite(t1,LOW);
        digitalWrite(t2,HIGH);
        Serial.println(t1);
        Serial.println(t2);
        
        //lcd_write("train is at 1km")
        while (ReadIr2 == 0)                            //wait for train to come from first ir to the 2nd ir
        {
            digitalWrite(op,HIGH); //car mcu starts working whenever the train is approaching. The red light will glow if car detected.else green light
            ReadIr2 = digitalRead(ir2);
            Serial.println("waiting for train to reach ir2: train is at around 1 km from the crossing");

        //condition1  0 1


        

            delay(500);
            if (ReadIr2 == 1)
            {
                goto A;
            }
            ReadIr2 = digitalRead(ir2);
            timeCounter+=1;
        }
    
    
    
    A: if ( ReadIr2 == 1 )
        { 
          for(pos=0;pos<=90;pos+=1)
          {
              servo.write(pos);
              //make buzzer high here with appropriate delays
              delay(25);
          }
          Serial.println("train has reached ir2: the train has arrived at 500 mts");
          digitalWrite(op,LOW); //car mcu stops working whenever the train is approaching. The red light will glow if car detected.else green light
          ReadIr4 = digitalRead(ir4);
          
          while (ReadIr4 == 0)
            {
                //lcd_write("waiting for train to reach ir4: train is less than 500 mts from the gate")
                Serial.println("train is less than 500 mts from the gate");

                            
            //condition1  1 0

            

        digitalWrite(t1,HIGH);
        digitalWrite(t2,LOW);
        Serial.println(t1);
        Serial.println(t2);
        
                delay(500);
                if (ReadIr4 == 1)
                {
                   goto B;
                }
                ReadIr4 = digitalRead(ir4);
                timeCounter+=1;
            }
        }
    
        
    
    
    B: if ( ReadIr4 == 1 )
        {
          //lcd_write(" calm....train has almost left")
          Serial.println("train reached ir 4: the train is leaving");
          ReadIr5 = digitalRead(ir5);
          while (ReadIr5 == 0)
          {
              //lcd_write("more calm...train has almost left")
              Serial.println("waiting for train to reach ir5: train has almost left");


       //condition1  1 1

        digitalWrite(t1,HIGH);
        digitalWrite(t2,HIGH);
        Serial.println(t1);
        Serial.println(t2);

              ReadIr5 = digitalRead(ir5);
              if (ReadIr5 == 1)
              {
                  goto C;
              }
              timeCounter+=1;
              delay(500);
          }
    C:    while (ReadIr5 == 1)
          {
              Serial.println("waiting for train to complete pass the IR5 : train is leaving(crossing the 5th gate)");
              ReadIr5 = digitalRead(ir5);
                      //condition1  0 0

        digitalWrite(t1,LOW);
        digitalWrite(t2,LOW);
        Serial.println(t1);
        Serial.println(t2);

              if (ReadIr5 == 0)
              {
                  goto D;
              }
              timeCounter+=1;
              delay(500);
          }
    D: if (ReadIr5 == 0)
          {
              Serial.println("track now clear: Train has left the craoosing. Crossing is now open again");
              for(pos=90;pos>=0;pos-=1)
            {
                servo.write(pos);
                //make buzzer high here with appropriate delays
                delay(25);
            }
    
          }
        }
          
          Serial.print("time taken is : ");
          Serial.print(timeCounter);
          if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
          {  

             String postStr = apiKey;
             postStr +="&field1=";
             postStr += String(timeCounter);
             postStr += "\r\n\r\n";
             client.print("POST /update HTTP/1.1\n");
             client.print("Host: api.thingspeak.com\n");
             client.print("Connection: close\n");
             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
             client.print("Content-Type: application/x-www-form-urlencoded\n");
             client.print("Content-Length: ");
             client.print(postStr.length());
             client.print("\n\n");
             client.print(postStr);
         }
         timeCounter=0;
      
                                        
 }




  else if (ReadIr5 == 1 )
  {
    
    servo.write(0);
    Serial.println("IR5 is activated :train is coming");
    //lcd_write("train is at 1km")
    ReadIr4 = digitalRead(ir4);
    while (ReadIr4 == 0)                            //wait for train to come from first ir to the 2nd ir
    {
      digitalWrite(op,HIGH); //car mcu starts working whenever the train is approaching. The red light will glow if car detected.else green light
      ReadIr4 = digitalRead(ir4);
      Serial.println("waiting for train to reach ir2: train is at around 1 km from the crossing");

       //condition1  0 1

        digitalWrite(t1,LOW);
        digitalWrite(t2,HIGH);
        Serial.println(0);
        Serial.println(1);

      delay(500);
      if (ReadIr4 == 1)
      {
        goto x;
      }
      timeCounter+=1;
      ReadIr4 = digitalRead(ir4);
    }



x: if ( ReadIr4 == 1 )
    { 
      for(pos=0;pos<=90;pos+=1)
      {
        servo.write(pos);
        delay(25);
      }
      Serial.println("train has reached ir4: the train has arrived at 500 mts");
      digitalWrite(op,HIGH); //car mcu starts working whenever the train is approaching. The red light will glow if car detected.else green light
      ReadIr2 = digitalRead(ir2);

      while (ReadIr2 == 0)
        {
          //lcd_write("waiting for train to reach ir2: train is less than 500 mts from the gate")
          Serial.println("train is less than 500 mts from the gate");

                  //condition1  1 0

        digitalWrite(t1,HIGH);
        digitalWrite(t2,LOW);
        Serial.println(t1);
        Serial.println(t2);


          delay(500);
          if (ReadIr2 == 1)
          {
            goto y;
          }
          ReadIr2 = digitalRead(ir2);
          timeCounter+=1;
        }
    }

    


y : if ( ReadIr2 == 1 )
    {
        //lcd_write(" calm....train has almost left")
        Serial.println("train reached ir 2: the train is leaving");
        ReadIr1 = digitalRead(ir1);
        while (ReadIr1 == 0)
        {
            //lcd_write("more calm...train has almost left")
            Serial.println("waiting for train to reach ir1: train has almost left");

        //condition1  1 1

        digitalWrite(t1,HIGH);
        digitalWrite(t2,HIGH);
Serial.println(t1);
        Serial.println(t2);


            ReadIr1 = digitalRead(ir1);
            if (ReadIr1 == 1)
            {
               goto z;
            }
            delay(500);
            timeCounter+=1;
        }
  z:    while (ReadIr1 == 1)
        {
            Serial.println("waiting for train to complete pass the IR1 : train is leaving(crossing the 5th gate)");
         //condition1  0 0

        digitalWrite(t1,LOW);
        digitalWrite(t2,LOW);
        Serial.println(t1);
        Serial.println(t2);

            ReadIr1 = digitalRead(ir1);
            if (ReadIr1 == 0)
            {
               goto v;
            }
            delay(500);
            timeCounter+=1;
        }
  v: if (ReadIr1 == 0)
        {
            Serial.println("track now clear: Train has left the craoosing. Crossing is now open again");
            for(pos=90;pos>=0;pos-=1)
          {
            servo.write(pos);
            delay(25);
          }

        }
      }
      Serial.print("time taken is : ");
      Serial.print(timeCounter);
      
      if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
      {  

         String postStr = apiKey;
         postStr +="&field1=";
         postStr += String(timeCounter);
         postStr += "\r\n\r\n";
         client.print("POST /update HTTP/1.1\n");
         client.print("Host: api.thingspeak.com\n");
         client.print("Connection: close\n");
         client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
         client.print("Content-Type: application/x-www-form-urlencoded\n");
         client.print("Content-Length: ");
         client.print(postStr.length());
         client.print("\n\n");
         client.print(postStr);
     }
     timeCounter=0;
                                           
                                        
                                        
 }


 delay(500);
}




