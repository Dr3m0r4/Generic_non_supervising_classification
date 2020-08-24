#include <iostream>
#include "CImg.h"
#include "KMeans.hpp"
#include "Computation.hpp"
#include "Metric.hpp"

using namespace cimg_library;
using T = double;

int main(int argc, char const *argv[]) {

  // srand(time(NULL)); // initialisation de rand
  std::string name, path_name("../images/");
  int nb_clusters(21), max_iter(100);
  bool choice(false);

  if (choice) {
    std::cout << "Enter the name of the image you want to analyse :" << '\n';
    std::cin >> name;
    std::cout << "Enter the number of clusters you want to determine :" << '\n';
    std::cin >> nb_clusters;
  } else {
    name = "tex2.tiff";
  }

  CImg<T> image((path_name+name).c_str()); // opening the image

  cimg_library::CImg<cimg_library::CImg<T>> desc(image.width(), image.height(), image.depth());

  int i(0);
  for (size_t x = 0; x < image.width(); x++) {
    for (size_t y = 0; y < image.height(); y++) {
      for (size_t z = 0; z < image.depth(); z++) {
        desc(x,y,z) = CImg<T>(4);
        desc(x,y,z)(0) = (T) x;
        desc(x,y,z)(1) = (T) y;
        desc(x,y,z)(2) = (T) z;
        T mean(0);
        for (size_t c = 0; c < image.spectrum(); c++) {
          mean += image(x,y,z,c);
        }
        mean /= image.spectrum();
        desc(x,y,z)(3) = mean;
      }
    }
  }

  CImgList<T> pro(5), con(5);
  CImg<T> res(5), quart(4);
  double def(0);
  for (size_t i = 0; i < pro.size(); i++) {
    pro(i) = CImg<T>(4,4);
    con(i) = CImg<T>(4,4);
    for (size_t j = 0; j < pro(i).width(); j++) {
      for (size_t k = 0; k < pro(i).height(); k++) {
        pro(i,j,k) = j*k;
        con(i,j,k) = j+k;
      }
    }
    res(i) = (pro(i)-con(i)).sqr().sum();
    quart = pro(i,2);
  }

  for (size_t i = 0; i < pro.size(); i++) {
    for (size_t j = 0; j < pro(i).wisth(); j++) {
      for (size_t k = 0; k < pro(i).height(); k++) {
        std::cout << pro(i,j,k) << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  for (size_t i = 0; i < quart.size(); i++) {
    std::cout << (int)quart(i) << ' ';
  }
  std::cout << '\n';

  def = sqrt(res.sum());
  for (size_t i = 0; i < res.size(); i++) {
    std::cout << (int)res(i) << ' ';
  }
  std::cout << '\n';
  std::cout << def << '\n';


  for (size_t j = 0; j < 4; j++) {
    std::cout << (int)desc(15,12)(j) << ' ';
  }
  std::cout << '\n';

  desc(15,12)/=2;

  for (size_t j = 0; j < 4; j++) {
    std::cout << (int)desc(15,12)(j) << ' ';
  }
  std::cout << '\n';

  CImgList<T> centr(nb_clusters);
  for (size_t i = 0; i < nb_clusters; i++) {
    centr(i)    = cimg_library::CImg<T>(4);
    centr(i)(0) = (T) (rand() % desc.width());
    centr(i)(1) = (T) (rand() % desc.height());
    centr(i)(2) = (T) (rand() % desc.depth());
    centr(i)(3) = (T) (rand() % 255);
  }

  // std::cout << desc.getDim() << '\n';

  // cimg_library::CImg<T> res = desc(5,6);
  // for (size_t i = 0; i < 4; i++) {
  //   std::cout << res(i) << " ";
  // }
  // std::cout << '\n';

  CImg<T> a(4), b(4);
  for (size_t i = 0; i < a.size(); i++) {
    a(i) = i;
    b(i) = i+1;
  }

  std::cout << Linf<T>(a,b) << " " << L2<T>(a,b) << '\n';
  a(2) = -5;
  a = a.abs().maxabs(3);
  for (size_t i = 0; i < a.size(); i++) {
    std::cout << a(i) << ' ';
  }
  std::cout << '\n';
  a -= b;
  for (size_t i = 0; i < b.size(); i++) {
    std::cout << a(i) << " ";
  }
  std::cout << '\n';
  b(3) = 9;

  b = (b-a).maxabs(5);
  for (size_t i = 0; i < b.size(); i++) {
    std::cout << b(i) << " ";
  }
  std::cout << '\n';
  std::cout << b.max() << '\n';
  std::cout << sqrt(81) << '\n';

  // image.display();

  CImg<T> result;
  CImgList<T> centroids;
  kmeans<T>(desc, nb_clusters, 100,1e-4, &(researchClusters<T>), &searchCentroids<T>, result, centroids, &L2<T>, &Linf<T>, false, "../images/resTex2.png");

  result.display();

  return 0;
}
