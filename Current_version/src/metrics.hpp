#ifndef METRIC_HPP
#define METRIC_HPP

#include <cmath>
#include "CImg.h"

/*
This interface will allow to implement other metrics.
This will be helpful for the evaluation of the Machine
Learning methods.
*/
template <typename T>
class Metric {
public:
  Metric() {};
  virtual T operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const = 0;
private:
};

template <typename T>
class Euclidian_square : public Metric<T> {
public:
  T operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const override;
private:
};

template <typename T>
class Euclidian : public Metric<T> {
public:
  T operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const override;
private:
};

#include "metrics.cxx"

#endif
