#include "Pixel.hpp"

Pixel::Pixel() {
  x = 0;
  y = 0;
  z = 0;
}

Pixel::Pixel(int a, int b, int c) {
  x = a;
  y = b;
  z = c;
}

void Pixel::assign(int a, int b, int c) {
  x = a;
  y = b;
  z = c;
}

Pixel& Pixel::operator=(const Pixel& p) {
  if (this != &p) {
    this->assign(p.getX(),p.getY(),p.getZ());
  }
  return *this;
}

int Pixel::getX() const {
  return x;
}

int Pixel::getY() const {
  return y;
}

int Pixel::getZ() const {
  return z;
}
