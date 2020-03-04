#ifndef __INCLUDE_CONFIG__
#define __INCLUDE_CONFIG__

// H-Bridge IO pins
const int MOTOR_L_A = 9;
const int MOTOR_L_B = 11;
const int MOTOR_R_A = 10;
const int MOTOR_R_B = 12;

// Microphone analog input pins
#define MIC_1 A0
#define MIC_2 A1
#define MIC_3 A2

// Microphone Posistions
int MIC_POS_1 = 180;
int MIC_POS_2 = 300;
int MIC_POS_3 = 60;

// Microphone Sample Count
const int SAMPLE_COUNT = 50;

// Behaviour constants
const int LOUD_VOLUME = 50;
const int SCARE_COOLDOWN = 1000;
const int SCARED_SPEED = 200;
const int NORMAL_SPEED = 30;
const int LOOP_DELAY = 10;

#endif
