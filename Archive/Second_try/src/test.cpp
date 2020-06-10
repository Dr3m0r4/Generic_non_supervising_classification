#include <iostream>
#include "Test.hpp"

using namespace cimg_library;

int main(int argc, char const *argv[]) {

  CImg<unsigned int> image("../images/dragon.jpeg");

  image.display("original");
  reverse(image).display("negatif");

  CImg<unsigned int> output = filter(image, 0);
  output.display("filtree");

  reverse(output).display("negatif filtre");

  return 0;
}
