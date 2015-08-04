#pragma once
#include <Servo.h>
#define SERV_NUM 4                  //number of servo for array
#define FRAME 20                    //interval time from current step to next step: 20msecc

//Pin outs
#define CENTER 4
#define RIGHT 5
#define LEFT 6
#define HEAD 7
#define DELAY 20

class PicoRobo {
public:
    void initServo();
    void playMotion(int motion[][SERV_NUM+1], int numberOfMotion);
    
protected:
    
private:
    int current_angle[SERV_NUM];
    int target_angle[SERV_NUM+1];
    float rotating_angle[SERV_NUM];      //rotating angle on each frame: calcurated by (target_angle - current_angle)/number of steps
    int servo_trim[SERV_NUM];            //trim to adjust each servo motors's angle to center
    
    Servo servo[SERV_NUM];

    void setCenterToServo();
    void moveToNextPosition();
};
