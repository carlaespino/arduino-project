/*TomaBrush
  Reads the movement of an accelerometer incorporated in a toothbrush and gives feedback.
  The feedback is given to the user by a change of state. (there is a change of colour of the leds).
  Also it helps count the time spend brushing by playing a song during 2 mintues when it detects brushing movement.
  If the time spend brushing is less than the recommended (2 minutes) it plays an advise message and it changes to an angry state.

  The circuit:
      Arduino Nano
      Analog sensor (2 axis accelerometer) attached to analog input 3 and 4
      Vibromotor attached to pin 3
      DfPlayer Mini Mp3 attached to digital pin 5 and 6
      2 leds (red and yellow) 

  Created 9 December 2016
  By Hans Lopez, Margalida Rius and Carla Espino
  This example code is in the public domain.
*/

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(5, 6); // RX, TX

#define MUSIC

const int led1 = 8; //yellow led
const int led2 = 9;  //red led
const int motorPin = 3; //vibration motor transistor connected to pin 3
int state = 0; // happy 0 , neutral 1, angry 2
int laststate = 0;

int arranque = 0;


unsigned long firststart = 0; //the start brushing millis for the first time
unsigned long start = 0; //start brushing millis
unsigned long finish = 0; //stop brushing millis
unsigned long timenotcleanning = 0;
unsigned long changetime = 0;

int xstaticval; //static x axis value of the accelerometer
int ystaticval; //static y axis value of the accelerometer

boolean brushing = 0; //check brushing movement
boolean movement = 0; // check movement
boolean music = false;
boolean isPlaying = false; 
boolean lastbrushing = 0;

//time
unsigned long m2 = 2*60*1000;  //2 minutes
unsigned long m30 = 30*60*1000; //30 minutes
unsigned long h6 = 6*60*60*1000; //6 hours
unsigned long m15 = 15*60*1000; //15 minutes

//accelerometer
const int numReadings = 10; //maximum index for array
const int numReadingsMov = 40;  

int readingsMov[numReadingsMov];  //the movement readings
int readingsx[numReadings];      // the readings from the accelerometer (x axis)
int readingsy[numReadings];      // the readings from the accelerometer (y axis)

int readIndexMov = 0;  // the index of the current reading
int readIndex = 0; 

int totalx = 0;                  // the running total
int totaly = 0;
int totalMov = 0;                
int averagex = 0;                // the average
int averagey = 0;                
float averageMov = 0;

int acelx = A4;  //the pin where we connect the analog read from the x axis of the accelerometer
int acely = A3;  //the pin where we connect the analog read from the y axis of the accelerometer


void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(motorPin, OUTPUT);

  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (20); //we set the volume of the speaker
  mp3_stop ();

  //we assign a 0 value to every value of the arrays
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readingsx[thisReading] = 0;
    readingsy[thisReading] = 0;
  }
  for (int thisReading = 0; thisReading < numReadingsMov; thisReading++) {
    readingsMov[thisReading] = 0;
  }

  delay(1);
  mp3_play(1);
  Serial.print("hi");
  mp3_play(1);
  digitalWrite(led1, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(1000);
  digitalWrite(led2, LOW);
  digitalWrite(motorPin, HIGH);
  delay(1000);
  digitalWrite(motorPin, LOW);
  delay(5000);
 }

void loop() {

  //----------CHECK MOTION----------------//

  ReadAccel();
  Changestate();
  Brushing();
  if (arranque == 0) {
    mp3_stop ();
    arranque++;
    xstaticval = analogRead(acelx);   //save the value of the x axis when the toothbrush is still
    ystaticval = analogRead(acely);   //save the value of the y axis when the toothbrush is still

    /*Serial.println("x");
      Serial.println(xstaticval);
      Serial.println("y");
      Serial.println(ystaticval);*/

  }

}


  //--------------CHANGE STATE--------------//

void Changestate() {

  state = constrain(state, 0, 2); //Constrain the state value from 0 to 2
  if (millis() - changetime  >= h6) { //Every 6 hours change the state from happy to neutral and to angry. It will stay angry until the kid brushes his teeth.
    if (state < 2) {
      state++;
    }
  }
  if (state != laststate) { //save the last state
    changetime = millis();
    laststate = state;
  }
  if (state == 0) { //happy state
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  if (state == 1) { //neutral state
    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);
    if (millis() - changetime == (h6 - 10000)) {
     mp3_play(3);
    }
  }
  if (state == 2) { //angry state
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    //claims for attention every hour and vibrates
    if (millis() % (m2 / 2) == 0) {
      digitalWrite (motorPin, HIGH); //vibrate
      delay (2500); //during this time
      digitalWrite (motorPin, LOW); //stop
    }
  }
}

//--------------READ ACCELEROMETER--------------//

void ReadAccel() {
  if (millis () % 10 == 0) {
    // subtract the last reading:
    totalx = totalx - readingsx[readIndex];
    totaly = totaly - readingsy[readIndex];
    totalMov = totalMov - readingsMov[readIndexMov];
    // read from the sensor:
    readingsx[readIndex] = analogRead(acelx);
    readingsy[readIndex] = analogRead(acely);
    readingsMov[readIndexMov] = movement;
    // add the reading to the total:
    totalx = totalx + readingsx[readIndex];
    totaly = totaly + readingsy[readIndex];
    totalMov = totalMov + readingsMov[readIndexMov];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    readIndexMov = readIndexMov + 1;

    // if we're at the end of the array... (readings array)
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
      /*Serial. print("y");
        Serial.println(averagey);
        Serial. print("x");
        Serial.println(averagex);*/
      //... calculate the average value
      averagex = totalx / numReadings;
      averagey = totaly / numReadings;
      //...check the average with the static values and change the movement value
      if ((abs( averagex - xstaticval) > 10) || (abs(averagey - ystaticval) > 10)) {
        movement = 1;
      } else {
        movement = 0;
      }
    }
     // if we're at the end of the array...(movement array)
    if (readIndexMov >= numReadingsMov) {
      // ...wrap around to the beginning:
      readIndexMov = 0;
      //... calculate the average value
      averageMov = totalMov / numReadingsMov;
      //...check the average and change the brushing value
      if (averageMov > 0.5) {
        lastbrushing = brushing;
        brushing = 1;
        //Serial.print("BRUSHING");
      } else {
        lastbrushing = brushing;
        brushing = 0;
        //Serial.print("NO BRUSHING");
      }
    }
  }//millis
}//Readaccel()

//--------------BRUSHING CODE--------------//

void Brushing() {

  // if it has been 15 minutes since the last start and the kid doesn't brush...
  if ((millis() - start) == m15) {
    state = 2;
    start = 0;
    finish = 0;
    timenotcleanning = 0;
    timenotcleanning = 0;
    arranque = 0;
  }
  //if start brushing movement
  if (brushing == 1 && lastbrushing == 0) {
    //primer inici
    mp3_play(2);
    if (start == 0) {
      firststart = millis();
    }
    //we save the millis() that the kid hasn't brushed his teeth
    if (finish > 0) {
      timenotcleanning = (finish - start) + timenotcleanning;
      //Serial.println(timenotcleanning);
      finish = 0;
    }
    start = millis();
    // music = true;
    //mp3_play(1);
    state = 0;
  }
  if (brushing == 1) {
    if (millis() - (firststart + timenotcleanning) >= m2) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      state = 0;
      mp3_stop();   
      //reset the variables
      start = 0;
      finish = 0;
      timenotcleanning = 0;
      firststart = 0;
      brushing = 0;
      movement = 0;
      lastbrushing = 0;
      delay(10);
      mp3_play(4);
      delay(m2/2);
      changetime = millis();
      arranque = 0;
    }
  }
  if (brushing == 0 && lastbrushing == 1) {
    finish = millis ();
    mp3_stop();
    if (millis() - start < m2) {
      state = 2;
      mp3_play(5);
    }
  }
}
