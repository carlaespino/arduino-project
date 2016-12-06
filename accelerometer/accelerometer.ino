//reading acceleration

/*
  accel sketch
  simple sketch to output values on the x- and y-axes
*/

const int xPin = A2; //analog input pins
const int yPin = A1;
const int zPin = A3;

void setup() {
  Serial.begin (9600); //note the higher than usual serial speed
}

void loop() {
  int xValue; //values from accelerometer stored here
  int yValue;
  int zValue;
  
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  zValue = analogRead(zPin);

 /* Serial.print("X value = ");
  Serial.println(xValue);

  Serial.print("Y value= ");
  Serial.println(yValue);*/
  
  Serial.print("Z value= ");
  Serial.println(yValue);
  delay(1000);
}


