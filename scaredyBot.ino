#include"Bearing.h"

//const int mic_1 = 7;
//const int mic_2 = 8;
//const int mic_3 = 9;

#define mic_1 A0
#define mic_2 A1
#define mic_3 A2

int intmax(int v1, int v2, int v3){
  int r = v1;
  if (v2 > r){
    r = v2;
  }
  if (v3 > r){
    r = v3;
  }
  return r;
}

const int trigger = 50;

int scare_time = 0;
int scare_cooldown = 1000;
void setup(){
  pinMode(mic_1, INPUT);
  pinMode(mic_2, INPUT);
  pinMode(mic_3, INPUT);
}

void loop(){
  int read_1 = analogRead(mic_1);
  int read_2 = analogRead(mic_2);
  int read_3 = analogRead(mic_3);
  int read_max = intmax(read_1, read_2, read_3);
  if (read_max > trigger){
    // Should now become scared
    scare_time = scare_cooldown;
  }
  
}
