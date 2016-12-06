int led1 = 10;
int led2 = 11;
int state = 0; // happy 0 , neutral 1, angry 2
int vibromotor;
int startBrushing = 0;
int brushingtime = 0;
int startAngry;

#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

boolean isPlaying = false;
const int motorPin = 3; //vibration motor transistor is connected to pin 3

int h6 = 6 * 60 * 60 * 1000;
int m30 = 30 * 60 * 1000;

Void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  mySerial.begin (9600);
  delay(1000);
  playFirst();
  isPlaying = true;

  if (millis() == 1000) { //After 1 second of starting the tomabrush
    //PlayMp3Message: hello! let’s start brushing your teeth!!
    Happy = 1;
  }

}

Void loop() {

  //--------------CHANGE STATE--------------//

  state = constrain(state,0,2);
  
  if (millis()%h6==0) { //Every 6 hours change the state
    state++
  }

  //When it has been on HappyState for 3 hours straight change to NeutralState
  if (
    (h12 >= millis() - happystart) // lkjjdas más de 12 horas
    &&
    (millis() > 121600000) 
    )
  {
    Happy = 0;
    Neutral = 1;
  } else if (121600000 => millis() - happystart ) {
    Neutral = 0;
    Angry = 1;
    startAngry = millis();
  }

  //----------BRUSHING CODE----------------//
  if (movement == 1) {
    Happy = 1; //Change the state to happy when the kid takes the tomabrush
  }


  if (brushing == 1 && startBrushing == 0) {
    startBrushing = millis();
  }

  if (brushing == 1) {
    if (millis() % 100 == 0) {
      brushingtime = startBrushing++;
    }
    Play music;
  }

  if (brushingtime - startBrushing >= 120000) {
    Happy = 1;
    Stop music;
    Play mp3 = Nice job!;
  }

  if (millis() - startBrushing = 60000 && brushingtime - startBrushing <= 30000) {
    PlayMp3 = You Should keep brushing your teeth!!
  }

  if (millis() - startBrushing = 120000 && brushingtime - startBrushing <= 95000) {
    PlayMp3 = You Should keep brushing your teeth!!
  }


  if (state == 2) { //angry state
    digitalWrite(led2 = HIGH);
    digitalWrite(led1 = LOW);
    //claims for attention every hour and vibrates
    if (millis() % 3600000 == 0) {
      play mp3;
      adviseMessage;
      digitalWrite (motorPin, HIGH); //vibrate
      delay (1000); //delay one second
      digitalWrite (motorPin, LOW);
    }
    if (millis() - startAngry == 10800000 /*3hours*/) {
      brushingtime = 0;
      startBrushing = 0;
    }
  }

  if (state == 0) { //happy state
    digitalWrite(led1 = HIGH);
    digitalWrite(led2 = LOW);

  }

  if (state == 1) { //neutral state
    digitalWrite(led2 = LOW);
    digitalWrite(led1 = LOW);
    brushingtime = 0;
    startBrushing = 0;
  }

}


