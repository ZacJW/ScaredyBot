#ifndef __INCLUDE_BEARING__
#define __INCLUDE_BEARING__

class Bearing{
  private:
    int b;
  public:
    Bearing();
    Bearing(int value);
    int getInt() const;
    Bearing operator +(Bearing const &other) const;
    Bearing operator -(Bearing const &other) const;
    int to(Bearing const &other) const;
    static const int modulo(const int a, const int b);
};
#endif
