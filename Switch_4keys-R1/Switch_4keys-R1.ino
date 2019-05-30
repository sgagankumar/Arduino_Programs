//connect SW 1-4 to SW0-4 on board and RST to COM on board
#define RST D4
#define SW1 D5
#define SW2 D6
#define SW3 D7
#define SW4 D8
int casevar,temp,c1=0,c2=0,c3=0,c4=0;

void setup() {
  // put your setup code here, to run once:
 pinMode(SW1, INPUT);
 pinMode(SW2, INPUT);
 pinMode(SW3, INPUT);
 pinMode(SW4, INPUT);
 pinMode(RST, OUTPUT);
 casevar=0;
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(casevar==1)
  {
    digitalWrite(RST,LOW);
  }
  else
  {
    digitalWrite(RST,HIGH);
  }
  c1=digitalRead(SW1);
  c2=digitalRead(SW2);
  c3=digitalRead(SW3);
  c4=digitalRead(SW4);
  if(c1==1)
  {
    Serial.println("Button 1 active");
    casevar=1;
  }
  else if(c2==1)
  {
    Serial.println("Button 2 active");
    casevar=1;
  }
  else if(c3==1)
  {
    Serial.println("Button 3 active");
    casevar=1;
  }
  else if(c4==1)
  {
    Serial.println("Button 4 active");
    casevar=1;
  }
  else
  {
    Serial.println("No button active");
    casevar=0;
  }
  delay(1000);
}
