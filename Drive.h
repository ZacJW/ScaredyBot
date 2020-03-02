#ifndef __INCLUDE_DRIVE__
#define __INCLUDE_DRIVE__

#include <Arduino.h>
#include "Bearing.h"
#include <FaBo9Axis_MPU9250.h>

class Drive{
  private:
    void drive_L(int speed);
    void drive_R(int speed);
    Bearing targetBearing;
    int targetSpeed;
    FaBo9Axis MPU;
    int L_A, L_B, R_A, R_B;
  public:
    Drive(int L_A, int L_B, int R_A, int R_B, FaBo9Axis &MPU);
    void forward(int speed);
    void forward(int speed, int steer);
    void backward(int speed);
    void backward(int speed, int steer);
    void left(int speed);
    void right(int speed);
    void toBearing(Bearing B);
    void setTarget(Bearing B, int speed);
    void alongTarget();
};

#endif
