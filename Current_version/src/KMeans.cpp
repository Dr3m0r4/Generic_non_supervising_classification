#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Functions.hpp"
#include "KMeans.hpp"

using namespace cimg_library;
using T = double;

int main(int argc, char const *argv[]) {

  srand(time(NULL)); // initialisation de rand
  std::string name, path_name("../images/");
  int nb_clusters(1);

  std::cout << "Enter the name of the image you want to analyse :" << '\n';
  std::cin >> name;
  CImg<T> image((path_name+name).c_str());
  T max_value = 255;

  average_grey(image);

  std::cout << "How many clusters do you want to identify ?" << '\n';
  std::cin >> nb_clusters;

  KMeans<T> kfisrt(image, nb_clusters);

  T* centroids = new T[nb_clusters];
  T* clusters = new T[nb_clusters];

  for (size_t i = 0; i < nb_clusters; i++) {
    centroids[i] = rand()/max_value;
    clusters[i] = i*max_value/nb_clusters;
  }

  kfisrt.display_centroids();

  // std::cout << image.depth() << '\n';

  image.display();

  return 0;
}
