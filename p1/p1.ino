#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>

String apiKey = "Your API of thingsspeak";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "Your wifi Network name";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Network password";
const char* server = "api.thingspeak.com";
int WET= 16; // Wet Indicator at Digital pin D0
int sensor = 13; 
int DRY= 2;  // Dry Indicator at Digital pin D4
int sense_Pin = 0; // sensor input at Analog pin A0
int Status = 12;
int value = 0;
const int buzzer =  4;

#define DHTPIN 0
DHT dht(DHTPIN, DHT11);
WiFiClient client;
void setup() 
{
   Serial.begin(9600);
   pinMode(buzzer, OUTPUT);
   pinMode(WET, OUTPUT);
   pinMode(DRY, OUTPUT);
   pinMode(sensor, INPUT);   // declare sensor as input
   pinMode(Status, OUTPUT);  // declare LED as output
   delay(2000);
    
//   Serial.begin(115200);
       delay(10);
       dht.begin();
 
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
  thingSpeak();
  fc_26();
  pir(); 
  
}


void thingSpeak()
{
   float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
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
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
void fc_26()
{
   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);

        if(value<50)
        {
            digitalWrite(WET, HIGH);
        }
       else
       {
           digitalWrite(DRY,HIGH);
       }

       delay(1000);

       digitalWrite(WET,LOW);

       digitalWrite(DRY, LOW);
}

void pir()
{
  long state = digitalRead(sensor);
    if(state == HIGH) 
    {
      digitalWrite (Status, HIGH);
      Serial.println("Motion detected!");
      digitalWrite(buzzer, HIGH);
      delay(1000);
    }
    else 
    {
      digitalWrite (Status, LOW);
      digitalWrite(buzzer, LOW);
      Serial.println("Motion absent!");
      delay(1000);
     }
}
