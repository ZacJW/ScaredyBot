#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "config.h"
#include "Bearing.h"
#include "Drive.h"
#include "mag_bearing.h"
#include "MicArray.h"

FaBo9Axis mpu;
Drive d = Drive(MOTOR_L_A, MOTOR_L_B, MOTOR_R_A, MOTOR_R_B, mpu);
MicArray mic_array = MicArray(MIC_1, MIC_POS_1, MIC_2, MIC_POS_2, MIC_3, MIC_POS_3);

void setup(){
  mic_array.begin();
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
  mic_array.sample(SAMPLE_COUNT);
  int vol = mic_array.getMaxVol();
  if (vol > LOUD_VOLUME){
    // Should now become scared
    scare_time = SCARE_COOLDOWN;
    Bearing runTo = mic_array.locateSound() + Bearing(180) + getBearing(mpu);
    d.setTarget(runTo, SCARED_SPEED);
    d.toBearing(runTo);
    d.alongTarget();
  }else if (scare_time > 0){
    d.alongTarget();
    scare_time--;
  }else{
    d.setTarget(mic_array.locateSound() + getBearing(mpu), NORMAL_SPEED);
    d.alongTarget();
  }
  delay(LOOP_DELAY);
}

