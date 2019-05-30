#include <ESP8266WiFi.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h> 

LiquidCrystal_I2C lcd(0x3f, 16, 2);

#define DHTPIN D4
DHT dht(DHTPIN, DHT11);

const char* ssid = "home";
const char* password = "12345678";
int timezone = 5 * 3600;
int dst = 0;

float temperature;
int day,mon,yrs,hrs,mins,sec,temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(D2,D3); 
  lcd.init(); 
  lcd.begin(16,2);
  lcd.backlight();
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print("Wifi ...");
  delay(5000);
  
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK"); 

  // check for correct time 
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

  Serial.print("Fetching correct Date and Time");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fetching Time");
  lcd.setCursor(0,1);
  lcd.print("From Internet");
  delay(5000);

  temp=(p_tm->tm_year + 1900);
  while(temp<2016)
  {
    Serial.print(".");
    temp=(p_tm->tm_year + 1900);
    delay(2000);
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);
  }
  
  day=p_tm->tm_mday;
  mon=p_tm->tm_mon + 1;
  yrs=p_tm->tm_year + 1900;
  hrs=p_tm->tm_hour;
  mins=p_tm->tm_min;
  sec=0;
  temperature = dht.readTemperature();
  while(isnan(temperature))
  {
    temperature = dht.readTemperature();
    delay(500);
  }
  
  // time zone: +5:30 INDIA
  
  if(mins>30)
  {
    hrs++;
  }
  mins=(mins+30)%60;
  if(hrs>23)
  {
    hrs=0;
    day++;
  }
}

void loop() {
  


  printdate();
  
  delay(5000);

  sec=sec+5;
  
  Serial.print("Room Temperature=");
  Serial.println(temperature);
  printtemp();
  delay(5000);

  sec=sec+5;

  timecheck();
}

void resettime()
{
    time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

  Serial.print("Fetching correct Date and Time");

  temp=(p_tm->tm_year + 1900);
  while(temp<2016)
  {
    Serial.print(".");
    temp=(p_tm->tm_year + 1900);
    delay(2000);
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);
  }
  
  day=p_tm->tm_mday;
  mon=p_tm->tm_mon + 1;
  yrs=p_tm->tm_year + 1900;
  hrs=p_tm->tm_hour;
  mins=p_tm->tm_min;
  sec=0;

  
  // time zone: +5:30 INDIA
  
  if(mins>30)
  {
    hrs++;
  }
  mins=(mins+30)%60;
  if(hrs>23)
  {
    hrs=0;
    day++;
  }
}

void printdate()
{
  Serial.print(hrs);
  Serial.print(":");
  Serial.print(mins);
  Serial.print(":");
  Serial.println(sec);

  Serial.print(day);
  Serial.print("/");
  Serial.print(mon);
  Serial.print("/");
  Serial.println(yrs);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TIME:");
  lcd.setCursor(6,0);
  lcd.print(hrs%12);
  lcd.setCursor(8,0);
  lcd.print(":");
  lcd.setCursor(9,0);
  lcd.print(mins);
  
  lcd.setCursor(0,1);
  lcd.print("DATE:");
  lcd.setCursor(6,1);
  lcd.print(day);
  lcd.setCursor(8,1);
  lcd.print("/");
  lcd.setCursor(9,1);
  lcd.print(mon);
  lcd.setCursor(11,1);
  lcd.print("/");
  lcd.setCursor(12,1);
  lcd.print(yrs);
}

void printtemp()
{
  temperature = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ROOM TEMPERATURE");
  lcd.setCursor(6,1);
  lcd.print(temperature);
  lcd.setCursor(8,1);
  lcd.print(" C ");
}

void timecheck()
{
    if(sec==60)
  {
    sec=0;
    mins++;
  }
  if(mins==60)
  {
    mins=0;
    hrs++; 
    temperature = dht.readTemperature();
  }
  if(hrs==24)
  {
    hrs==0;
    day++;
    
    //if wifi available update with real time
    if( WiFi.status() == WL_CONNECTED )
    {
      resettime();
    }
  }
  if(day==32)
  {
    if(mon==(1||3||5||7||8||10||12))
    {
      day=1;
      mon++;
    }
  }
  if(day==31)
  {
    if(mon==(4||6||9||11))
    {
      day=1;
      mon++;
    }
  }
  if(mon==2)
  {
    if(day==29)
    {
      day=1;
      mon++;
    }
  }
  if(mon==13)
  {
    mon=1;
    yrs++;
  }
}

