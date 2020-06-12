#ifndef METRIC_HPP
#define METRIC_HPP

/*
This file provide some metrics to compute different
Machine Learning methods.
*/
#include <cmath>
#include "CImg.h"

/*
This interface came to easier the way to implement
some new metrics.
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

template <typename T>
class Non_Euclidian_square : public Metric<T> {
public:
  T operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const override;
private:
};

template <typename T>
class Non_Euclidian : public Metric<T> {
public:
  T operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const override;
private:
};

template <typename T>
class Linf : public Metric<T> {
public:
  T operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const override;
private:
};

#include "metrics.cxx"

#endif
