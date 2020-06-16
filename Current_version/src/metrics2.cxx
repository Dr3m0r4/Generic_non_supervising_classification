template <typename T>
T Euclidian_square<T>::operator()(Pixel<T> a, Pixel<T> b) const {
  T result(0);
  for (size_t i = 0; i < 4; i++) {
    result += std::pow(a[i]-b[i],2);
  }
  return result;
}

template <typename T>
T Euclidian<T>::operator()(Pixel<T> a, Pixel<T> b) const {
  return std::sqrt(Euclidian_square<T>()(a, b));
}

template <typename T>
T Non_Euclidian_square<T>::operator()(Pixel<T> a, Pixel<T> b) const {
  T result(0);
  for (size_t i = 0; i < 4; i++) {
    result += std::pow(a[i]-b[i],2);
  }
  return result;
}

template <typename T>
T Non_Euclidian<T>::operator()(Pixel<T> a, Pixel<T> b) const {
  return std::sqrt(Non_Euclidian_square<T>()(a, b));
}

template <typename T>
T Linf<T>::operator()(Pixel<T> a, Pixel<T> b) const {
  T result(0);
  // for (size_t i = 0; i < 4; i++) {
  for (size_t i = 0; i < 3; i++) {
    result = std::fmax(result, std::abs(b[i]-a[i]));
  }
  result = std::fmax(result, std::abs(b[3]-a[3])/20);
  return result;
}

template <typename T>
T Lone<T>::operator()(Pixel<T> a, Pixel<T> b) const {
  T result(0);
  // for (size_t i = 0; i < 4; i++) {
  for (size_t i = 0; i < 3; i++) {
    result += std::abs(b[i]-a[i]);
  }
  return result;
}
