template <typename T>
T Euclidian_square<T>::operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const {
  T result(0);
  for (size_t i = 0; i < 3; i++) {
    result += pow(a[i]-b[i],2);
  }
  result += pow(img(a[0],a[1],a[2])-img(b[0],b[1],b[2]),2);
  return result;
}

template <typename T>
T Euclidian<T>::operator()(const cimg_library::CImg<T>& img, int a[3], int b[3]) const {
  return sqrt(Euclidian_square<T>()(img, a, b));
}
