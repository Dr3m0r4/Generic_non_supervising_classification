#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "CImg.h"
#include "metrics.hpp"
#include <iostream>

template <typename T = unsigned int, typename Met = Euclidian<unsigned int>>
class KMeans {
public:
  KMeans(cimg_library::CImg<T> image, int nb_c);
  void display_centroids();
  T get_distance(int i, int x, int y);
  void grey();
  void compute();
private:
  cimg_library::CImg<T> img;
  cimg_library::CImg<T> output;
  int width, height, depth, spectrum;
  size_t nb_clusters;
  int** centroids;
  Metric<T>* distance;
  T* clusters;
  const T max_value = 255;
};

#include "KMeans.cxx"

#endif
