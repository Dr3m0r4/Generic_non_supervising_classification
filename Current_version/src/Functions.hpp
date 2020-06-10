#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "CImg.h"

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

#endif
