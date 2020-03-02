#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "config.h"
#include "Bearing.h"
#include "Drive.h"
#include "mag_bearing.h"

FaBo9Axis mpu;
Drive d = Drive(MOTOR_L_A, MOTOR_L_B, MOTOR_R_A, MOTOR_R_B, mpu);


struct sample_data {
  int min_B = 1023;
  int max_B = 0;
  int min_FL = 1023;
  int max_FL = 0;
  int min_FR = 1023;
  int max_FR = 0;
};

sample_data sample(int sample_size); // work-around prototype for annoying IDE auto prototype before struct nonsense
sample_data sample(int sample_size){
  sample_data data;
  for (int i = 0; i < sample_size; i++){
    int B = analogRead(MIC_1);
    if (B < data.min_B){
      data.min_B = B;
    }
    if (B > data.max_B){
      data.max_B = B;
    }
    int FL = analogRead(MIC_2);
    if (FL < data.min_FL){
      data.min_FL = FL;
    }
    if (FL > data.max_FL){
      data.max_FL = FL;
    }
    int FR = analogRead(MIC_3);
    if (FR < data.min_FR){
      data.min_FR = FR;
    }
    if (FR > data.max_FR){
      data.max_FR = FR;
    }
  }
  return data;
}

Bearing locateSound(int vol_B, int vol_FL, int vol_FR){
  if (vol_FL < vol_B && vol_FL < vol_FR){
    // Source is between back and front-right
    int diff_B = vol_B - vol_FL;
    int diff_FR = vol_FR - vol_FL;
    return Bearing((diff_B*120)/(diff_B + diff_FR) + 60);
  }else if(vol_FR < vol_B && vol_FR < vol_FL){
    // Source is between back and front-left
    int diff_B = vol_B - vol_FR;
    int diff_FL = vol_FL - vol_FR;
    return Bearing((diff_FL*120)/(diff_B + diff_FL) + 180);
  }else{
    // Source is between front-left and front-right
    int diff_FL = vol_FL - vol_B;
    int diff_FR = vol_FR - vol_B;
    return Bearing((diff_FR*120)/(diff_FL + diff_FR) + 300);
  }
}



void setup(){
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  pinMode(MIC_3, INPUT);
  if (!mpu.begin()) {
    // flash pin 13 led indicating mpu connection failure
    pinMode(13, OUTPUT);
    while(1){
      digitalWrite(13,HIGH);
      delay(100);
      digitalWrite(13,LOW);
      delay(100);
    }
  }
}

void loop(){
  static int scare_time = 0;
  sample_data data = sample(SAMPLE_COUNT);
  int vol_B = data.max_B - data.min_B;
  int vol_FL = data.max_FL - data.min_FL;
  int vol_FR = data.max_FR - data.min_FR;
  int vol = vol_B;
  vol = (vol_FL > vol) ? vol_FL : vol;
  vol = (vol_FR > vol) ? vol_FR : vol;
  if (vol > LOUD_VOLUME){
    // Should now become scared
    scare_time = SCARE_COOLDOWN;
    Bearing runTo = locateSound(vol_B, vol_FL, vol_FR) + Bearing(180) + getBearing(mpu);
    d.setTarget(runTo, SCARED_SPEED);
    d.toBearing(runTo);
    d.alongTarget();
  }else if (scare_time > 0){
    d.alongTarget();
    scare_time--;
  }else{
    d.setTarget(locateSound(vol_B, vol_FL, vol_FR) + getBearing(mpu), NORMAL_SPEED);
    d.alongTarget();
  }
  delay(LOOP_DELAY);
}

