#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;

int trackCount = 4; // Number of MP3 files on the SD card
int triggerTime = 400; //How long you have to hold to trigger a sound

unsigned long startTime = 0;
boolean touching = false;
boolean held = false;

int readPins[] = {A0,A1,A2,A3,A4,A5};
int pinCount = 6;

void setup() {
  
  Serial.begin(9600);
  
  for (int i = 0; i < pinCount; i++) {

      pinMode(readPins[i],INPUT);
      digitalWrite(readPins[i],HIGH);
    
  }  
  
  //start the shield
  
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();

  //start playing track 1
  MP3player.playTrack(1);
}


void loop() {

  // Count active touches

  int touchCount = 0;

  for (int i = 0; i < pinCount; i++) {
    if ( digitalRead(readPins[i]) == LOW ) touchCount++;
  }

  // Play logic

  if ( touchCount >= 2 ) {

    if (!touching) {
      touching = true;
      held = false;
      startTime = millis();
    }
  } 
  else {
    if (touching) {
      touching = false ;
      held = false;
    }
  }

  // Play sound after a long enough hold

  if ( touching && (millis() - startTime > triggerTime)) {

    if (!held) {
      held = true;
      playSound();
    }
  }

}

void playSound() {

  int trackNumber = random(trackCount) + 1;
  
  Serial.println(trackNumber);
  
  MP3player.playTrack(trackNumber);

}
