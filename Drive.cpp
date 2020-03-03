#include "Drive.h"
#include <FaBo9Axis_MPU9250.h>
#include "mag_bearing.h"
#include "Bearing.h"

Drive::Drive(int L_A, int L_B, int R_A, int R_B, FaBo9Axis &MPU){
  // Set H-bridge control pins to OUTPUT and pwm to 0
  pinMode(L_A, OUTPUT);
  pinMode(L_B, OUTPUT);
  pinMode(R_A, OUTPUT);
  pinMode(R_B, OUTPUT);
  analogWrite(L_A, 0);
  analogWrite(L_B, 0);
  analogWrite(R_A, 0);
  analogWrite(R_B, 0);
  this->L_A = L_A;
  this->L_B = L_B;
  this->R_A = R_A;
  this->R_B = R_B;
  this->MPU = MPU;
}

void Drive::drive_L(int speed){
  if (speed < 0){
    // Reverse
    speed = (speed < -255) ? 255 : -speed;
    analogWrite(L_A, 0);
    analogWrite(L_B, speed);
  }else{
    // Forward
    speed = (speed > 255) ? 255 : speed;
    analogWrite(L_B, 0);
    analogWrite(L_A, speed);
  }
}
void Drive::drive_R(int speed){
  if (speed < 0){
    // Reverse
    speed = (speed < -255) ? 255 : -speed;
    analogWrite(R_A, 0);
    analogWrite(R_B, speed);
  }else{
    // Forward
    speed = (speed > 255) ? 255 : speed;
    analogWrite(R_B, 0);
    analogWrite(R_A, speed);
  }
}

void Drive::forward(int speed){
  drive_L(speed);
  drive_R(speed);
}
void Drive::forward(int speed, int steer){
  drive_L(speed + steer);
  drive_R(speed - steer);
}
void Drive::backward(int speed){
  drive_L(-speed);
  drive_R(-speed);
}
void Drive::backward(int speed, int steer){
  drive_L(-speed + steer);
  drive_R(-speed - steer);
}
void Drive::left(int speed){
  drive_L(-speed);
  drive_R(speed);
}
void Drive::right(int speed){
  drive_L(speed);
  drive_R(-speed);
}

void Drive::toBearing(Bearing B){
  // Get current bearing
  Bearing current = getBearing(MPU);
  int diff = current.to(B);
  while (abs(diff) > 10){
     if(diff < 0){
      // Drive Left
      left(200);
     }else{
      // Drive Right
      right(200);
     }
     delay(10);
     // Get new bearing
     current = getBearing(MPU);
     diff = current.to(B);
  }
  forward(0);
}

void Drive::setTarget(Bearing B, int speed){
  this->targetBearing = B;
  this->targetSpeed = speed;
}

void Drive::alongTarget(){
  Bearing current = getBearing(MPU);
  int diff = current.to(this->targetBearing);
  forward(this->targetSpeed, diff);
}

