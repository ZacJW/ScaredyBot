#ifndef __INCLUDE_DRIVE__
#define __INCLUDE_DRIVE__

#include <Arduino.h>
#include "Bearing.h"
#include <FaBo9Axis_MPU9250.h>

static const int motor_L_A = 9;
static const int motor_L_B = 11;
static const int motor_R_A = 10;
static const int motor_R_B = 12;

class Drive{
  private:
    void drive_L(int speed);
    void drive_R(int speed);
    Bearing targetBearing;
    int targetSpeed;
  public:
    Drive();
    void forward(int speed);
    void forward(int speed, int steer);
    void backward(int speed);
    void backward(int speed, int steer);
    void left(int speed);
    void right(int speed);
    void toBearing(Bearing B, FaBo9Axis &MPU);
    void setTarget(Bearing B, int speed);
    void alongTarget(FaBo9Axis &MPU);
};

#endif
