int sensor1 = D1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(sensor1, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int value1 = digitalRead(sensor1);
  Serial.println(value1);
  delay(1000);
}
