template <typename T, typename Met>
KMeans<T, Met>::KMeans(cimg_library::CImg<T> image, int nb_c) {
  img.assign(cimg_library::CImg<T>(image));
  nb_clusters = nb_c;
  width = img.width(); height = img.height(); depth = img.depth();
  spectrum = img.spectrum();
  centroids = new int*[nb_clusters]; clusters = new T[nb_clusters];

  output.assign(cimg_library::CImg<T>(width,height,depth,spectrum,0));
  for (size_t i = 0; i < nb_clusters; i++) {
    centroids[i] = new int[2];
    centroids[i][0] = rand() % width;
    centroids[i][1] = rand() % height;
    clusters[i] = i*max_value/nb_clusters;
  }

  distance = new Met;
}

template <typename T, typename Met>
void KMeans<T, Met>::display_centroids() {
  for (size_t i = 0; i < nb_clusters; i++) {
    std::cout << "centroid " << i << " x : " << centroids[i][0] << " | y : " << centroids[i][1] << '\n';
  }
  std::cout << '\n';
}

#include <stdexcept>
template <typename T, typename Met>
T KMeans<T, Met>::get_distance(int i, int x, int y) {
  if (i >= nb_clusters ||
      x >= width ||
      y >= height ||
      x < 0 || y < 0 || i < 0) {
        throw std::invalid_argument( "one of the argument isn't correct !!");
  }

  int a(centroids[i][0]), b(centroids[i][1]);

  T result(0);

  result = (*distance)(img(a,b),img(x,y));

  return result;
}

template <typename T, typename Met>
void KMeans<T, Met>::grey() {

  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      for (size_t z = 0; z < depth; z++) {
        T sum = 0;
        for (size_t c = 0; c < spectrum; c++) {
          sum += img(x,y,z,c);
        }
        sum /= spectrum;
        for (size_t c = 0; c < spectrum; c++) {
          img(x,y,z,c) = sum;
        }
      }
    }
  }

}

template <typename T, typename Met>
void KMeans<T, Met>::compute() {
}
