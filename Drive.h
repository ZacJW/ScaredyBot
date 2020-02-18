#ifndef __INCLUDE_DRIVE__
#define __INCLUDE_DRIVE__

#include<Arduino.h>

static const int motor_L_A = 9;
static const int motor_L_B = 11;
static const int motor_R_A = 10;
static const int motor_R_B = 12;

class Drive{
  private:
    void drive_L(int speed);
    void drive_R(int speed);
  public:
    Drive();
    void forward(int speed);
    void forward(int speed, int steer);
    void backward(int speed);
    void backward(int speed, int steer);
    void left(int speed);
    void right(int speed);
};

#endif
