#ifndef MLEARNING_HPP
#define MLEARNING_HPP

#include "CImg.h"
#include "metrics2.hpp"

/*
Interface to help to implement other Machine Learning methods
*/
template <typename T, typename Met>
class MLearning {
public:
  virtual T get_distance(int i, int x, int y, int z) const = 0;
  virtual void compute(double tol) = 0;
private:
};

#endif
