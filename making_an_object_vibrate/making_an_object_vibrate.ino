//making an object vibrate

/*
vibrate sketch
vibrate for one second every minute
*/

const int motorPin = 3; //vibration motor transistor is connected to pin 3

void setup() {
  pinMode (motorPin, OUTPUT);
}

void loop() {
  digitalWrite (motorPin, HIGH); //vibrate
  delay (1000); //delay one second
  digitalWrite (motorPin, LOW);
  delay (5000); //wait 59 seconds
}
