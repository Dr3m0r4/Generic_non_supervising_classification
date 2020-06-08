#include <iostream>
#include <string>
#include "ML.hpp"

using namespace mlpack;
using namespace mlpack::kmeans;
using namespace cimg_library;

int main(int argc, char const *argv[]) {
  std::cout << "Hello world !!" << '\n';

  // Different things tried with CImg
  CImg<unsigned int> image("../images/dragon.jpeg");
  // std::cout << '\n';
  // image.display();
  // std::cout << '\n';

  std::cout << image(0,0,0) << " " << image(0,0,1) << " " << image(0,0,2) << " " << image(0,0) << '\n'; // x,y,spectre=0
  CImgList<> g = image.get_gradient();
  std::cout << "width :" << image.width() << " ; height :" << image.height() << '\n';
  int x, y;
  std::cout << "enter the x variable and then the y variable :" << '\n';
  std::cin >> x >> y;
  std::cout << "x :" << x << " and y :" << y << '\n';
  std::cout << "dx : " << g(0)(x,y) << " and dy : " << g(1)(x,y) << '\n';

  /*
  Part where I am trying to test new things with the mnist dataset, CImg and MLpack
  */
  std::cout << '\n';
  std::string folder_name("../images/training/");
  std::string fic_name(folder_name+"0.png");
  std::cout << folder_name << '\n' << '\n';

  CImg<unsigned int> mnist(fic_name.c_str());
  // std::cout << '\n';
  // mnist.display();
  // std::cout << '\n';

  CImgList<> h = mnist.get_gradient();
  std::cout << "width :" << mnist.width() << " ; height :" << mnist.height() << '\n';
  std::cout << "enter the x variable and then the y variable :" << '\n';
  std::cin >> x >> y;
  std::cout << "x : " << x << " and y : " << y << '\n';
  std::cout << "pixel : " << mnist(x,y) << '\n'; // niveau de gris
  std::cout << "dx : " << h(0)(x,y) << " and dy : " << h(1)(x,y) << '\n';

  int width(mnist.width()), height(mnist.height());
  arma::Mat<double> data(width,height); // arma::mat is aka arma::Mat<double>
  fill_data(data, mnist);
  // int i,j;
  // for (i=0;i<width;i++)
  // {
  //   for (j=0;j<height;j++)
  //   {
  //     data(i,j) = mnist(i,j);
  //   }
  // }
  // std::cout << "\n" << data << "\n\n";
  CImg<unsigned int> morille(width, height, 1, 1, 0);
  out_data(data, morille);
  morille.save_png("../images/histo.png");


  // First try of MLpack
  KMeans<> k;
  arma::mat matrix(5,5);
  arma::Row<int> assignements();
  std::cout << matrix << '\n'; // << assignements << '\n';
  return 0;
}
