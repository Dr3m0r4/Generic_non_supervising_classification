template <typename T>
Pixel<T>::Pixel() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
  this->v = 0;
}

template <typename T>
Pixel<T>::Pixel(T a, T b, T c, T v) {
  this->x = a;
  this->y = b;
  this->z = c;
  this->v = v;
}

template <typename T>
void Pixel<T>::assign(T a, T b, T c, T v) {
  this->x = a;
  this->y = b;
  this->z = c;
  this->v = v;
}

template <typename T>
Pixel<T>& Pixel<T>::operator=(const Pixel<T>& p) {
  if (this != &p) {
    this->assign(p.getX(),p.getY(),p.getZ(),p.getV());
  }
  return *this;
}

template <typename T>
const T& Pixel<T>::operator[](int i) const {
  switch (i) {
    case 0:
      return x;
      break;
    case 1:
      return y;
      break;
    case 2:
      return z;
      break;
    case 3:
      return v;
      break;
  }
}

template <typename T>
T& Pixel<T>::operator[](int i) {
  switch (i) {
    case 0:
      return x;
      break;
    case 1:
      return y;
      break;
    case 2:
      return z;
      break;
    case 3:
      return v;
      break;
  }
}

template <typename T>
T Pixel<T>::getX() const {
  return this->x;
}

template <typename T>
T Pixel<T>::getY() const {
  return this->y;
}

template <typename T>
T Pixel<T>::getZ() const {
  return this->z;
}

template <typename T>
T Pixel<T>::getV() const {
  return this->v;
}
