#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "CImg.h"
#include "Functions.hpp"
#include <iostream>

template <typename T = unsigned int>
class KMeans {
public:
  KMeans(cimg_library::CImg<T> img, int nb_c);
  void display_centroids();
private:
  cimg_library::CImg<T> input;
  cimg_library::CImg<T> output;
  int width, height, depth, spectrum;
  int nb_clusters;
  int** centroids;
  T* clusters;
  const T max_value = 255;
};

template <typename T>
KMeans<T>::KMeans(cimg_library::CImg<T> img, int nb_c) {
  input.assign(cimg_library::CImg<T>(img));
  nb_clusters = nb_c;
  width = img.width(); height = img.height(); depth = img.depth();
  spectrum = img.spectrum();
  centroids = new int*[nb_clusters]; clusters = new T[nb_clusters];

  output.assign(cimg_library::CImg<T>(width,height,depth,spectrum,0));
  for (size_t i = 0; i < nb_clusters; i++) {
    centroids[i] = new int[2];
    centroids[i][0] = rand() % width;
    centroids[i][1] = rand() % height;
    clusters[i] = i*max_value/nb_clusters;
  }
}

template <typename T>
void KMeans<T>::display_centroids() {
  for (size_t i = 0; i < nb_clusters; i++) {
    std::cout << "centroid " << i << " x : " << centroids[i][0] << " | y : " << centroids[i][1] << '\n';
  }
  std::cout << '\n';
}

#endif
