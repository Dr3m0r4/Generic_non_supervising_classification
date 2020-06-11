#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "MLearning.hpp"
#include <iostream>

/*
The metric name is passed as the second type for template.
The metric should be write like 'Metric<T>' with 'T' the
typename we want to work with.
*/

/*
This class is a first implementation of the KMeans and it
will serve as a basis for the next implementations.
*/
template <typename T = unsigned int, typename Met = Euclidian<unsigned int>>
class KMeans : MLearning<T, Met> {
public:
  KMeans(cimg_library::CImg<T> image, int nb_c, size_t itermax = 100);
  void display_centroids();
  void display_centroids(int i);
  T get_distance(int i, int x, int y, int z) const override;
  T get_distance(int i, int x, int y) const; // return the distance between the $i^th$ centroids and the pixel (x,y) when image is 2D
  void grey(); // fill the image with average grey to be worked with
  void fill_output();
  void compute(T tol) override; // algorithm of the method
private:
  cimg_library::CImg<T> img;
  cimg_library::CImg<T> output;
  size_t width, height, depth, spectrum;
  size_t nb_clusters;
  int** centroids;
  T* clusters;
  size_t max_iter;
  const T max_value = 255;
};

template <typename T>
bool operator<(const cimg_library::CImg<T>& A, T b);

template <typename T>
bool operator>(const cimg_library::CImg<T>& A, T b);

#include "KMeans.cxx"

#endif
