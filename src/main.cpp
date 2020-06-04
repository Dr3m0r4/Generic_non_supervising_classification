#include <iostream>
#include "CImg.h"
#include <mlpack/methods/kmeans/kmeans.hpp>

using namespace mlpack::kmeans;
using namespace cimg_library;

int main(int argc, char const *argv[]) {
  std::cout << "Hello world !!" << '\n';
  CImg<unsigned int> image("../images/dragon.jpeg");
  std::cout << image(0,0,0) << " " << image(0,0,1) << " " << image(0,0,2) << " " << image(0,0) << '\n'; // x,y,spectre=0
  CImgList<> g = image.get_gradient();
  std::cout << "width :" << image.width() << " ; length :" << '\n';
  std::cout << g(0)(5,10) << '\n';
  KMeans<> k;
  arma::mat matrix(5,5);
  arma::Row<int> assignements;
  std::cout << matrix << '\n';
  return 0;
}
