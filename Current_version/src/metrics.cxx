template <typename T>
T Euclidian_square<T>::operator()(const T& a, const T& b) const {
  return pow(a-b,2);
}

template <typename T>
T Euclidian<T>::operator()(const T& a, const T& b) const {
  return sqrt(pow(a-b,2));
}
