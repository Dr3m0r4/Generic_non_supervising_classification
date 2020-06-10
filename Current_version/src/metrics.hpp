#ifndef METRIC_HPP
#define METRIC_HPP

#include <cmath>

template <typename T>
class Metric {
public:
  Metric() {};
  virtual T operator()(const T& a, const T& b) const = 0;
private:
};

template <typename T>
class Euclidian_square : public Metric<T> {
public:
  T operator()(const T& a, const T& b) const override;
private:
};

template <typename T>
class Euclidian : public Metric<T> {
public:
  T operator()(const T& a, const T& b) const override;
private:
};

#include "metrics.cxx"

#endif
