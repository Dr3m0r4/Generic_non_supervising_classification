#ifndef ML_HPP
#define ML_HPP

#include <mlpack/methods/kmeans/kmeans.hpp>
#include "CImg.h"

template <typename T=int, typename M=double>
void fill_data(arma::Mat<M>& matrix,const cimg_library::CImg<T>& image)
{
  int width(image.width()), height(image.height());
  int i,j;
  for (i=0;i<width;i++)
  {
    for (j=0;j<height;j++)
    {
      matrix(i,j) = image(i,j);
    }
  }
}

template <typename T=int, typename M=double>
void out_data(const arma::Mat<M>& matrix, cimg_library::CImg<T>& image)
{
  int width(image.width()), height(image.height());
  int i,j;
  for (i=0;i<width;i++)
  {
    for (j=0;j<height;j++)
    {
      image(i,j) = matrix(i,j);
    }
  }
}

#endif
