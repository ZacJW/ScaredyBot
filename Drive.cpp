#include"Drive.h"


Drive::Drive(){
  // Set H-bridge control pins to OUTPUT and pwm to 0
  pinMode(motor_L_A, OUTPUT);
  pinMode(motor_L_B, OUTPUT);
  pinMode(motor_R_A, OUTPUT);
  pinMode(motor_R_B, OUTPUT);
  analogWrite(motor_L_A, 0);
  analogWrite(motor_L_B, 0);
  analogWrite(motor_R_A, 0);
  analogWrite(motor_R_B, 0);
}

void Drive::drive_L(int speed){
  if (speed < 0){
    // Reverse
    speed = (speed < -255) ? 255 : -speed;
    analogWrite(motor_L_A, 0);
    analogWrite(motor_L_B, speed);
  }else{
    // Forward
    speed = (speed > 255) ? 255 : speed;
    analogWrite(motor_L_A, speed);
    analogWrite(motor_L_B, 0);
  }
}
void Drive::drive_R(int speed){
  if (speed < 0){
    // Reverse
    speed = (speed < -255) ? 255 : -speed;
    analogWrite(motor_R_A, 0);
    analogWrite(motor_R_B, speed);
  }else{
    // Forward
    speed = (speed > 255) ? 255 : speed;
    analogWrite(motor_R_A, speed);
    analogWrite(motor_R_B, 0);
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
  Bearing current;
  int diff = current.to(B)
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
     // current = getBearing();
     diff = current.to(B);
  }
}
