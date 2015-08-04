#include <Servo.h>
#include <Arduino.h>
#include "PicoRobo.h"
//====================================================================================================================
//Parameter
//====================================================================================================================
#define SERV_NUM 4                  //number of servo for array
#define FRAME 20                    //interval time from current step to next step: 20msecc

int current_angle[SERV_NUM];
int target_angle[SERV_NUM+1];
float rotating_angle[SERV_NUM];      //rotating angle on each frame: calcurated by (target_angle - current_angle)/number of steps
int servo_trim[SERV_NUM];            //trim to adjust each servo motors's angle to center
int servo_limit[SERV_NUM];           //limit to prevent each motor going to bad places

Servo servo[SERV_NUM];
#define CENTER 4
#define RIGHT 5
#define LEFT 6
#define NECK 7
#define DELAY 50

//====================================================================================================================
//Servo Method
//====================================================================================================================
void PicoRobo::initServo(){
    
  //attach pins to each servo
  servo[0].attach(CENTER);
  servo[1].attach(RIGHT);
  servo[2].attach(LEFT);
  servo[3].attach(NECK);
  
  //set trim
  int tmp_trim[SERV_NUM]={0,-4,3,0};      //set trim to each servo
  int tmp_limit[SERV_NUM]={40,15,15,75};      //set trim to each servo
  
  for(int i=0;i<SERV_NUM;i++){
    servo_trim[i]=tmp_trim[i];
    servo_limit[i]=tmp_limit[i];
  }
  
  //rotate all servos to center position
  setCenterToServo();
}

void PicoRobo::setCenterToServo(){
  for(int i=0;i<SERV_NUM;i++){
    servo[i].write(90 + servo_trim[i]);
    current_angle[i] = 0;
    target_angle[i] = 0;
  }
}

//move to next position
void PicoRobo::moveToNextPosition(){
  
  //check limit
   for(int i=0;i<SERV_NUM;i++){
     if(target_angle[i]>servo_limit[i]){
       target_angle[i]=servo_limit[i];
     }else if(target_angle[i]<-servo_limit[i]){
       target_angle[i]=-servo_limit[i];
     }
   }
  
  int numberOfStep = target_angle[SERV_NUM]/FRAME;    //total number of steps to move to next position
  
  for(int i=0;i<SERV_NUM;i++){
    rotating_angle[i]=((float)target_angle[i]-(float)current_angle[i])/(float)numberOfStep;
  }
  
  int next_timing = millis() + FRAME;
  int current_time;
  float tmp_angle[SERV_NUM];
  
  for(int i=0;i<SERV_NUM;i++){
    tmp_angle[i]=(float)current_angle[i];
  }
  
  while(numberOfStep){
    current_time=millis();
    if(current_time>next_timing){
      for(int i=0;i<SERV_NUM;i++){
        tmp_angle[i] += rotating_angle[i];
        current_angle[i] = (int)tmp_angle[i];
        servo[i].write(current_angle[i]+servo_trim[i]+90);        
      }
      next_timing = next_timing + FRAME;
      numberOfStep--;
    }
  }
  //adjust current_angle
  for(int i=0;i<SERV_NUM;i++){
    current_angle[i] = target_angle[i];
    servo[i].write(current_angle[i]+servo_trim[i]+90);
  }
}

//call moveToNextPosition() method continuously
void PicoRobo::playMotion(int motion[][SERV_NUM+1], int numberOfMotion){
  for(int i=0;i<numberOfMotion;i++){
    for(int j=0;j<SERV_NUM+1;j++){
      target_angle[j]=motion[i][j];
    }
    moveToNextPosition();
  }
}

