#ifndef TEST_HPP
#define TEST_HPP

#include "CImg.h"
#include <string>

template <typename T=unsigned int>
class ML {
public:
  virtual void fit() = 0;
private:
  unsigned int nb_clusters;
  unsigned int max_iter;
  T* centroids;
  std::string metric;
  cimg_library::CImg<T> input;
  cimg_library::CImg<T> output;
};

template <typename T=unsigned int>
class KMeans : public ML<T> {
public:
private:
};

template <typename T=unsigned int>
cimg_library::CImg<T> colorizer(const cimg_library::CImg<T>& image, int color=0) {
  int width(image.width()), height(image.height()), spectrum(image.spectrum()), nb_colors(1);
  if (color) {
    color--;
    nb_colors = spectrum;
  }
  cimg_library::CImg<T> result(width, height, 1, nb_colors, 0);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int sum = 0;
      for (int c = 0; c < spectrum; c++) {
        sum += image(x,y,c);
      }
      result(x,y,color) = sum/spectrum;
    }
  }

  return result;
}

template <typename T=unsigned int>
cimg_library::CImg<T> filter(const cimg_library::CImg<T>& image, int color) {
  int width(image.width()), height(image.height()), spectrum(image.spectrum());

  cimg_library::CImg<T> result(width, height, 1, spectrum, 0);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      result(x,y,color) = image(x,y,color);
    }
  }

  return result;
}

template <typename T=unsigned int>
cimg_library::CImg<T> reverse(const cimg_library::CImg<T>& image, int color=0) {
  int width(image.width()), height(image.height()), spectrum(image.spectrum());

  cimg_library::CImg<T> result(width, height, 1, spectrum, 255);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      for (int c = 0; c < spectrum; c++) {
        result(x,y,c) -= image(x,y,c);
      }
    }
  }

  return result;
}

#endif
