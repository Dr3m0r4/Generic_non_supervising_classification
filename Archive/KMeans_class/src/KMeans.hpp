#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "MLearning.hpp"
#include "Functions.hpp"
#include "Pixel.hpp"

#include <iostream>
#include <vector>

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
  // Constructors
  KMeans(cimg_library::CImg<T> image, int nb_c, size_t itermax = 100);
  // Display
  void display_centroids() const;
  void display_centroids(int i) const;
  // Methods
  T get_distance(int i, int x, int y, int z) const override;
  T get_distance(int i, int x, int y) const;
    /*
    return the distance between the $i^th$ centroids and the pixel (x,y) when image is 2D
    */
  // Computation
  void compute(T tol) override; // algorithm of the method
private:
  // Private methods
  void grey(); // fill the image with average grey to be worked with
  void fill_output();
  void compute_centroids();
  // double** diff_centroids(int** old_centr);
  double diff_centroids();
  bool compare_centroids(double** diff, double tol);
private:
  cimg_library::CImg<T> img;
  cimg_library::CImg<T> output;
  size_t width, height, depth, spectrum;
  size_t nb_clusters, max_iter;
  // int** centroids;
  // T* clusters;
  std::vector<Pixel<T>> centroids;
  std::vector<Pixel<T>> old_centr;
  std::vector<T> clusters;
  std::vector<Pixel<T>>* vect_p;
  T max_value;
};


#include "KMeans.cxx"

#endif
