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
    void playString(char * motion);
    
protected:
    
private:
    int moveSpeed;
    
    Servo servo;
    void setCenterToServo();
    void moveToNextTarget();
    int  charToString(char h, char t, char u);
};
