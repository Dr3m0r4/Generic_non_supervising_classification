#ifndef METRIC_HPP
#define METRIC_HPP

/*
This file provide some metrics to compute different
Machine Learning methods.
*/
#include <cmath>
#include "Pixel.hpp"

/*
This interface came to easier the way to implement
some new metrics.
*/
template <typename T>
class Metric {
public:
  Metric() {};
  virtual T operator()(Pixel<T> a, Pixel<T> b) const = 0;
private:
};

template <typename T>
class Euclidian_square : public Metric<T> {
public:
  T operator()(Pixel<T> a, Pixel<T> b) const override;
private:
};

template <typename T>
class Euclidian : public Metric<T> {
public:
  T operator()(Pixel<T> a, Pixel<T> b) const override;
private:
};

template <typename T>
class Non_Euclidian_square : public Metric<T> {
public:
  T operator()(Pixel<T> a, Pixel<T> b) const override;
private:
};

template <typename T>
class Non_Euclidian : public Metric<T> {
public:
  T operator()(Pixel<T> a, Pixel<T> b) const override;
private:
};

template <typename T>
class Linf : public Metric<T> {
public:
  T operator()(Pixel<T> a, Pixel<T> b) const override;
private:
};

template <typename T>
class Lone : public Metric<T> {
public:
  T operator()(Pixel<T> a, Pixel<T> b) const override;
private:
};

#include "metrics2.cxx"

#endif
