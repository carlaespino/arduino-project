
int led1 = 10;
int led2 = 11;
int state = 0; // happy 0 , neutral 1, angry 2
int vibromotor;
int start = 0;
int brushingtime = 0;
int startAngry;

boolean isPlaying = false;
const int motorPin = 3; //vibration motor transistor is connected to pin 3

int h6 = 6 * 60 * 60 * 1000;
int m30 = 30 * 60 * 1000;
int m2 = 2 * 60 * 1000;

Void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  mySerial.begin (9600);

  //PlayMp3Message: hello! let’s start brushing your teeth!!;

}

Void loop() {

  //--------------CHANGE STATE--------------//

  state = constrain(state, 0, 2);

  if (millis() % h6 == 0) { //Every 6 hours change the state from happy to angry. It will stay angry until the kid brushes his teeth.
    state++;
  }
  if (state == 0) { //happy state
    digitalWrite(led1 = HIGH);
    digitalWrite(led2 = LOW);
  }
  if (state == 1) { //neutral state
    digitalWrite(led2 = LOW);
    digitalWrite(led1 = LOW);
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
  }
  
  //----------CHECK MOTION----------------//
  ReadAccel();
  if (
    (x < 400 && x > 250) &&
    (y < 400 && y > 250) &&
    (z < 220 && z > 200)) {
    brushing = 0;
  } else {
    brushing = 1;
  }

  //----------BRUSHING CODE----------------//

  if (brushing == 1 && lastbrushing == 0) {
    start = millis();
  }

  if (brushing == 1) {

    if (millis() - start >= m2) {
      state = 0;
      //Stop music;
      //Play mp3 = Nice job!;
    } else {
      //play music;
    }

  }

  if (brushing == 0 && lastbrushing == 1) {
    if (millis() - start < m2) {
      state = 2;
      //Play mp3 = You should keep brushing your teeth!;
    }

  }

}

