#include <Servo.h>

#include "PicoRobo.h"
#include "movelist.h"

PicoRobo body;

void setup() {
  body.initServo();
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char cmd = Serial.read();
    
    switch (cmd){  
      case 'w':
        body.playMotion(move_forward, 6);
        break; 
      case 's':
        body.playMotion(move_back, 6);
        break;
      case 'a':
        body.playMotion(turn_left, 7);
        break;
      case 'd':
        body.playMotion(turn_right, 7);
        break;      
      case 'j':
        body.playMotion(look_around, 5);
        break;
      case 'k':
        body.playMotion(home_position, 1);
        break;
      case 'p':
        body.playMotion(dance_left, 6);
        break;
      case '[':
        body.playMotion(creep_left, 1);
        break;
      case ']':
        body.playMotion(creep_right, 1);
        break;
      case 'o':
        body.playMotion(dance_o, 5);
        break;
      case '\n':
      case '\r':
        break;
      default:
        Serial.write("wsad - move\n");
        Serial.write("j - scan\n");
        Serial.write("k - home\n");
        Serial.write("p - leg dance\n");
        Serial.write("[ - look left\n");
        Serial.write("] - look right\n");
        Serial.write("o - stomp\n");
    }
  }
  delay(200);
}
