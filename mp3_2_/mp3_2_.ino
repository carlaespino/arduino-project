///              MP3 PLAYER PROJECT
/// http://educ8s.tv/arduino-mp3-player/
//////////////////////////////////////////


#include "SoftwareSerial.h"
#include "DFPlayer_Mini_Mp3.h"

SoftwareSerial mySerial(10, 11);

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

int buttonNext = 2;
int buttonPrevious = 4;
boolean isPlaying = false;
const int motorPin = 3; //vibration motor transistor is connected to pin 3
int button = 13;
int led = 12;
int lastbutton = 0;
int buttonvalue;

void setup () {


  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonPrevious, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin (9600);
  delay(1000);

}

void loop () {
  if (millis() % 10000 == 0) {
    mp3_play(1);
  }
}


