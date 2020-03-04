#ifndef __INCLUDE_MICARRAY__
#define __INCLUDE_MICARRAY__
#include "Bearing.h"
#include <Arduino.h>
class MicArray{
  public:
    MicArray(int pin_1, int pos_1, int pin_2, int pos_2, int pin_3, int pos_3);
    MicArray(int pin_1, Bearing pos_1, int pin_2, Bearing pos_2, int pin_3, Bearing pos_3);
    void begin();
    void sample(int sample_size);
    int getVol_1();
    int getVol_2();
    int getVol_3();
    void getVol(int &vol_1, int &vol_2, int &vol_3);
    int getMaxVol();
    Bearing locateSound();
  private:
    int pin_1, pin_2, pin_3;
    Bearing pos_1, pos_2, pos_3;
    int _1_to_2, _2_to_3, _3_to_1;
    int vol_1, vol_2, vol_3;
};

#endif
