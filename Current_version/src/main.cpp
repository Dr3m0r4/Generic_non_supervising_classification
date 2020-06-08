#include <iostream>
#include "ML.hpp"

using namespace cimg_library;

int main(int argc, char const *argv[]) {

  CImg<unsigned int> image("../images/tex5.tiff");

  std::cout << '\n';
  image.display();
  std::cout << '\n';

  return 0;
}
