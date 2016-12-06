
int led1 = 8;
int led2 = 9;
int state = 0; // happy 0 , neutral 1, angry 2
int vibromotor;
int start = 0;
int brushingtime = 0;
boolean brushing = 1;
boolean music = false;
boolean lastbrushing = 1;
int startAngry;

boolean isPlaying = false;
const int motorPin = 3; //vibration motor transistor is connected to pin 3

unsigned long h6 = 21600000;
unsigned long m30 = 1800000;
unsigned long m2 = 120000;

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); // RX, TX

//Analog read pins
const int xPin = A1;
const int yPin = A2;
const int zPin = A3;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these

int minVal = 265;
int maxVal = 402;

int lastx;
int lasty;
int lastz;
int interval = 10;

//to hold the caculated values
double x;
double y;
double z;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (22);


  mp3_stop ();
  //PlayMp3Message: hello! let’s start brushing your teeth!!;

}

void loop() {

  //----------CHECK MOTION----------------//

  if (millis() % 1000 == 0) {
    lastbrushing = brushing;
    ReadAccel();

    if ((lastx <= interval + x && lastx > x - interval) &&
        (lasty <= interval + y && lasty > y - interval) &&
        (lastz <= interval + z && lastz > z - interval)) {

      brushing = 0;
      Serial.println(brushing);

    } else {

      brushing = 1;
      Serial.println(brushing);
    }
  }





  //----------BRUSHING CODE----------------//

  if (brushing == 1 && lastbrushing == 0) {
    start = millis();
    music = true;
    PlayMusic();
  }

  if (brushing == 1) {

    if (millis() - start >= m2) {
      state = 0;

      //  mp3_stop();
      //Play mp3 = Nice job!;
    }

  }

  if (brushing == 0 && lastbrushing == 1) {
    if (millis() - start < m2) {
      state = 2;
      //Play mp3 = You should keep brushing your teeth!;
    }

  }

  //--------------CHANGE STATE--------------//
  /*
    state = constrain(state, 0, 2);

    if (millis() % h6 == 0) { //Every 6 hours change the state from happy to angry. It will stay angry until the kid brushes his teeth.
      state++;
    }
    if (state == 0) { //happy state
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }
    if (state == 1) { //neutral state
      digitalWrite(led2, LOW);
      digitalWrite(led1, LOW);
    }

    if (state == 2) { //angry state
      digitalWrite(led2, HIGH);
      digitalWrite(led1, LOW);
      //claims for attention every hour and vibrates
      if (millis() % 3600000 == 0) {
        //play mp3;
        //adviseMessage;
        digitalWrite (motorPin, HIGH); //vibrate
        delay (1000); //delay one second
        digitalWrite (motorPin, LOW);
      }
    }*/
}



void PlayMusic() {
  if (music == true) {
    mp3_play(1);
    music = false;
  }
}

void ReadAccel() {

  lastx = x;
  lasty = y;
  lastz = z;

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  delay(10);
  //Output the caculations

}







