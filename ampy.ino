#include <Servo.h>

#include "PicoRobo.h"
#include "movelist.h"

PicoRobo body;

char look_around3[] =  "s200h+00"
                      "|s300h+65"
                      "|s300h+00"
                      "|h-75"
                      "|h+00";

void setup() {
  body.initServo();
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char cmd = Serial.read();
    char moveBuffer[200];
    switch (cmd){  
      case 'w':
        Serial.write("starting\n");
        body.playString(look_around3);
        Serial.write("\nstoping\n");
        break; 
      case 's':
        //body.standBy();
        break;
    }
  }
  delay(200);
}
