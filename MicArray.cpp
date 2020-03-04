#include "MicArray.h"

MicArray::MicArray(int pin_1, int pos_1, int pin_2, int pos_2, int pin_3, int pos_3){
  this->pin_1 = pin_1;
  this->pin_2 = pin_2;
  this->pin_3 = pin_3;
  this->pos_1 = Bearing(pos_1);
  this->pos_2 = Bearing(pos_2);
  this->pos_3 = Bearing(pos_3);
  _1_to_2 = this->pos_1.to(this->pos_2);
  _2_to_3 = this->pos_2.to(this->pos_3);
  _3_to_1 = this->pos_3.to(this->pos_1);
}

MicArray::MicArray(int pin_1, Bearing pos_1, int pin_2, Bearing pos_2, int pin_3, Bearing pos_3){
  this->pin_1 = pin_1;
  this->pin_2 = pin_2;
  this->pin_3 = pin_3;
  this->pos_1 = pos_1;
  this->pos_2 = pos_2;
  this->pos_3 = pos_3;
  _1_to_2 = this->pos_1.to(this->pos_2);
  _2_to_3 = this->pos_2.to(this->pos_3);
  _3_to_1 = this->pos_3.to(this->pos_1);
}

void MicArray::begin(){
  digitalWrite(pin_1, LOW);
  digitalWrite(pin_2, LOW);
  digitalWrite(pin_3, LOW);
  pinMode(pin_1, INPUT);
  pinMode(pin_2, INPUT);
  pinMode(pin_3, INPUT);
}

void MicArray::sample(int sample_size){
  int min_1, max_1, min_2, max_2, min_3, max_3;
  for (int i = 0; i < sample_size; i++){
    int read_1= analogRead(pin_1);
    if (read_1< min_1){
      min_1 = read_1;
    }
    if (read_1> max_1){
      max_1 = read_1;
    }
    int read_2 = analogRead(pin_2);
    if (read_2 < min_2){
      min_2 = read_2;
    }
    if (read_2 > max_2){
      max_2 = read_2;
    }
    int read_3 = analogRead(pin_3);
    if (read_3 < min_3){
      min_3 = read_3;
    }
    if (read_3 > max_3){
      max_3 = read_3;
    }
  }
  vol_1 = max_1 - min_1;
  vol_2 = max_2 - min_2;
  vol_3 = max_3 - min_3;
}

int MicArray::getVol_1(){
  return vol_1;
}

int MicArray::getVol_2(){
  return vol_2;
}

int MicArray::getVol_3(){
  return vol_3;
}

void MicArray::getVol(int &vol_1, int &vol_2, int &vol_3){
  vol_1 = this->vol_1;
  vol_2 = this->vol_2;
  vol_3 = this->vol_3;
}

int MicArray::getMaxVol(){
  int val = vol_1;
  val = (vol_2 > val) ? vol_2 : val;
  val = (vol_3 > val) ? vol_3 : val;
  return val;
}

Bearing MicArray::locateSound(){
  if(vol_3 < vol_1 && vol_3 < vol_2){
    // Source is between mic_1 and mic_2
    int diff_1 = vol_1 - vol_3;
    int diff_2 = vol_2 - vol_3;
    return Bearing((diff_2*_1_to_2)/(diff_1 + diff_2)) + pos_1;
  }else if(vol_1 < vol_2 && vol_1 < vol_3){
    // Source is between mic_2 and mic_3
    int diff_2 = vol_2 - vol_1;
    int diff_3 = vol_3 - vol_1;
    return Bearing((diff_3*_2_to_3)/(diff_2 + diff_3)) + pos_2;
  }else{
    // Source is between mic_1 and mic_3
    int diff_1 = vol_1 - vol_2;
    int diff_3 = vol_3 - vol_2;
    return Bearing((diff_1*_3_to_1)/(diff_1 + diff_3)) + pos_3;
  }
}

