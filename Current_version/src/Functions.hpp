#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "CImg.h"

// Functions
template <typename T = unsigned int>
void average_grey(cimg_library::CImg<T>& img) {
  // using size_t = unsigned int;
  size_t width(img.width()), height(img.height()), depth(img.depth()), spectrum(img.spectrum());

  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      for (size_t z = 0; z < depth; z++) {
        T sum = 0;
        for (size_t c = 0; c < spectrum; c++) {
          sum += img(x,y,z,c);
        }
        sum /= spectrum;
        for (size_t c = 0; c < spectrum; c++) {
          img(x,y,z,c) = sum;
        }
      }
    }
  }
}

// Operators
template <typename T>
bool operator<(const cimg_library::CImg<T>& A, T b) {
  size_t width(A.width()), height(A.height()), depth(A.depth());
  size_t x(0), y(0), z(0);
  bool result(True);
  while (x < width && result) {
    for (size_t y = 0; y < height; y++) {
      for (size_t z = 0; z < depth; z++) {
        result = result && A(x,y,z)<b;
      }
    }
    x++;
  }
  return result;
}

template <typename T>
bool operator>(const cimg_library::CImg<T>& A, T b) {
  size_t width(A.width()), height(A.height()), depth(A.depth());
  size_t x(0), y(0), z(0);
  bool result(True);
  while (x < width && result) {
    for (size_t y = 0; y < height; y++) {
      for (size_t z = 0; z < depth; z++) {
        result = result && A(x,y,z)>b;
      }
    }
    x++;
  }
  return result;
}

#endif
