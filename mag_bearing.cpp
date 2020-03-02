#include "Bearing.h"
#include "mag_bearing.h"
#include "mpu_bias.h"
#include <FaBo9Axis_MPU9250.h>

Bearing getBearing(FaBo9Axis &MPU){
  float x, y, z;
  MPU.readMagnetXYZ(&x,&y,&z);
  x = (x + X_HARD_BIAS);
  y = (y + Y_HARD_BIAS) * Y_SOFT_BIAS;
  return Bearing(atan2(x,y)*180/PI);
}

