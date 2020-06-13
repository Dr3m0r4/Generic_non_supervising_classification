#ifndef PIXEL_HPP
#define PIXEL_HPP

template <typename T>
class Pixel {
public:
  // Constructors
  Pixel();
  Pixel(T a, T b, T c, T v);
  // Affectation
  void assign(T a, T b, T c, T v);
  Pixel<T>& operator=(const Pixel<T>& p);
  const T& operator[](int i) const;
  T& operator[](int i);
  // Getters
  T getX() const;
  T getY() const;
  T getZ() const;
  T getV() const;
private:
  T x, y, z;
  T v;
};

#include "Pixel.cxx"

#endif
