int sensor1 =16;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(sensor1, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(sensor1);

  Serail.println(value);
  delay(1000);
}
