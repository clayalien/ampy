#include <Servo.h> 
#include <Arduino.h>

//====================================================================================================================
//Parameter
//====================================================================================================================
#include "PicoRobo.h"
int moveSpeed;
int headCurrent;
int headTarget;

Servo servo;

void PicoRobo::initServo(){
    
  //attach pins to each servo
  servo.attach(HEAD);
 
  //rotate all servos to center position
  setCenterToServo();
}

void PicoRobo::setCenterToServo(){
  servo.write(90);
  moveSpeed = 300;
  headCurrent = 0;
  headTarget = 0;
}

//move to next position
void PicoRobo::moveToNextTarget(){
  servo.write(headTarget + 90);
  delay(1000);
}


void PicoRobo::playString(char * motion){
  char h,t,u = '0';
  char sign = '+';
  int i = 0;
  while(motion[i] != 0) {
    char c = motion[i];
    switch(c){
      case 's':
       h = motion[++i];
       t = motion[++i];
       u = motion[++i];
       moveSpeed = charToString(h,t,u);
       break;
      case 'h':
       sign = motion[++i];
       t = motion[++i];
       u = motion[++i];
       headTarget = charToString('0',t,u);
       if (sign == '-'){
        headTarget = -headTarget;
       }
       break;
      case '|':
       moveToNextTarget();
       break;
    }
    i++;
  }
  moveToNextTarget();
}

int PicoRobo::charToString(char h, char t, char u){
   int temp = u - '0';
   temp +=   (t - '0') * 10;
   temp +=   (h - '0') * 100;

   return temp;
}

