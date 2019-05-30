void setup() {
Serial.begin(9600);
pinMode(D1,INPUT);
pinMode(D2,INPUT);
pinMode(D3,OUTPUT);
pinMode(D4,OUTPUT);
digitalWrite(D3,HIGH);
digitalWrite(D4,LOW);
}


void loop() {
  int sensor=digitalRead(D1);
  Serial.println(sensor);
  delay(1000);
}
