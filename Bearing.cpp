#include "Bearing.h"
Bearing::Bearing(){
  this->b = 0;
}
Bearing::Bearing(int value){
  this->b = modulo(value, 360);
}
int Bearing::getInt() const{
  return this->b;
}
Bearing Bearing::operator + (Bearing const &other) const{
  return Bearing(this->b + other.b);
}
Bearing Bearing::operator - (Bearing const &other) const{
  return Bearing(this->b - other.b);
}
int Bearing::to(Bearing const &other) const{
  int val = other.b - this->b;
  return (val > 180) ? val-360 : (val < -180) ? val+360 : val;
}
const int Bearing::modulo(const int a, const int b){
  int val = a % b;
  return (val < 0) ? val + b : val;
}


