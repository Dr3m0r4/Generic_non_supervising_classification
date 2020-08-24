#ifndef METRIC_HPP
#define METRIC_HPP

#include "CImg.h"

/*
to obtain a good Metric, you should use this model
*/
template <typename T>
double Linf(
  cimg_library::CImg<T> a,
  cimg_library::CImg<T> b
) {
  if (a.size() != b.size()) {
    throw cimg_library::CImgAbortException("The images have not the same dimensions");
  }
  double result(0);
  result = (a-b).abs().max();

  return result;
}

template <typename T>
double L2(
  cimg_library::CImg<T> a,
  cimg_library::CImg<T> b
) {
  if (a.size() != b.size()) {
    throw cimg_library::CImgAbortException("The images have not the same dimensions");
  }
  double result(0);
  result = sqrt((a-b).sqr().sum());

  return result;
}

#endif
