void setup(){
Serial.begin(9600);
pinMode(A0, INPUT);// Communication started with 9600 baud
}
void loop(){
int sensor=analogRead(A0); // Incoming analog signal read and appointed sensor
Serial.println(sensor); 
delay(1000);//Wrote serial port
}
