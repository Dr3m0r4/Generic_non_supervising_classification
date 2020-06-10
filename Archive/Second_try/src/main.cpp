#include <iostream>
#include "CImg.h"

using namespace cimg_library;

int main(int argc, char const *argv[]) {

  int x, y;
  CImg<unsigned int> image("../images/tex1.tiff");

  std::cout << "Choose the placement of a pixel within 0 and " << image.width()-1 << " and between 0 and " << image.height()-1 << '\n';

  std::cin >> x >> y;
  std::cout << "The pixel's value is : ";
  for (int i = 0; i < image.spectrum(); i++) {
    std::cout << image(x,y,i) << " ";
  }
  std::cout << '\n';

  std::cout << '\n';
  image.display();
  std::cout << '\n';

  return 0;
}
