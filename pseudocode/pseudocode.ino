int led1 = 10;
int led2 = 11;
int Happy = 0;
int Neutral = 0;
int Angry = 0;
int vibromotor;
int startBrushing = 0;
int brushingtime = 0;
int startAngry;

Void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

Void loop() {

  if (millis() == 1000) { //After 1 second of starting the tomabrush
PlayMp3Message: hello! let’s start brushing your teeth!!
    Happy = 1;
  }
}
//--------------CHANGE STATE--------------//

//Assign a happy and neutral start millis in order to count the HappyState and NeutralState active time
if (HappyState passa de 0 a 1) {
  happystart = millis();
}

//When it has been on HappyState for 3 hours straight change to NeutralState
if (60800000 => millis() - happystart < 121600000) {
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
    Happy=1;
    Stop music;
    Play mp3 = Nice job!;
  }
  
   if (millis() - startBrushing = 60000 && brushingtime - startBrushing <= 30000) {
    PlayMp3 = You Should keep brushing your teeth!!
  }

   if (millis() - startBrushing = 120000 && brushingtime - startBrushing <= 95000) {
    PlayMp3 = You Should keep brushing your teeth!!
  }


if (Angry == 1) {
  digitalWrite(led2 = HIGH);
  digitalWrite(led1 = LOW);
  //claims for attention every hour and vibrates
  if (millis() % 3600000 == 0) {
    play mp3;
    adviseMessage;
    vibromotor = HIGH;
  }
  if (millis() - startAngry == 10800000 /*3hours*/) {
    brushingtime = 0;
    startBrushing = 0;
  }
}

if (Happy == 1) {
  digitalWrite(led1 = HIGH);
  digitalWrite(led2 = LOW);

}

if (Neutral == 1) {
  digitalWrite(led2 = LOW);
  digitalWrite(led1 = LOW);
  brushingtime = 0;
  startBrushing = 0;
}

