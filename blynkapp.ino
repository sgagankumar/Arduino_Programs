#include <Adafruit_Sensor.h>
#define BLYNK_PRINT Serial
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>





char auth[]="c4a28467496c4f7d9ffb40cd9ccf76d3";
char ssid[] = "home";
char pass[] = "12345678";
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //Defining the pin and the dhttype
BlynkTimer timer;
void sendSensor()
{



float h = dht.readHumidity();
float t = dht.readTemperature();
  

0  if (isnan(h) || isnan(t))
  {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }

 
Blynk.virtualWrite(V5 , h);
Blynk.virtualWrite(V6 , t);



}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
 
  delay(10);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
