// Constructors
template <typename T, typename Met>
KMeans<T, Met>::KMeans(cimg_library::CImg<T> image, int nb_c, size_t itermax) {
  img.assign(cimg_library::CImg<T>(image));
  nb_clusters = nb_c;
  width = img.width(); height = img.height(); depth = img.depth();
  spectrum = img.spectrum();
  centroids = new int*[nb_clusters]; clusters = new T[nb_clusters+1];

  output.assign(cimg_library::CImg<T>(width,height,depth,1,0));
  clusters[0] = 0;
  for (size_t i = 0; i < nb_clusters; i++) {
    centroids[i] = new int[3];
    centroids[i][0] = rand() % width;
    centroids[i][1] = rand() % height;
    centroids[i][2] = rand() % depth;
    clusters[i+1] = (i+1)*max_value/(nb_clusters+1);
  }

  max_iter = itermax;
}

// Display
template <typename T, typename Met>
void KMeans<T, Met>::display_centroids() {
  for (size_t i = 0; i < nb_clusters; i++) {
    std::cout << "centroid " << i << " x : " << centroids[i][0] << " | y : " << centroids[i][1] << " | z : " << centroids[i][2] << '\n';
  }
  std::cout << '\n';
}

template <typename T, typename Met>
void KMeans<T, Met>::display_centroids(int i) {
  std::cout << "centroid " << i << " x : " << centroids[i][0] << " | y : " << centroids[i][1] << " | z : " << centroids[i][2] << '\n';
}

// Methods
#include <stdexcept>
template <typename T, typename Met>
T KMeans<T, Met>::get_distance(int i, int x, int y, int z) const {
  if (i >= nb_clusters ||
      x >= width ||
      y >= height ||
      z >= depth ||
      x < 0 || y < 0 || z < 0 || i < 0) {
        throw std::invalid_argument( "one of the argument isn't correctly bound !!");
  }

  int a(centroids[i][0]), b(centroids[i][1]), c(centroids[i][2]);

  T result(0);
  int inter[3] = {x, y, z};

  result = Met()(img, centroids[i], inter);

  return result;
}

template <typename T, typename Met>
T KMeans<T, Met>::get_distance(int i, int x, int y) const {
  if (depth>1) {
    throw std::invalid_argument( "The image isn't 2D" );
  }

  return KMeans<T, Met>::get_distance(i,x,y,0);
}

// Computation
template <typename T, typename Met>
void KMeans<T, Met>::compute(T tol) {
  size_t iter(0);
  cimg_library::CImg<T> old_output(output);
  fill_output();
  bool stop((output-old_output)>tol);
  while (iter < max_iter && stop) {
    iter++;
    old_output = output;
    for (size_t i = 1; i < nb_clusters+1; i++) {

    }
    output.display("before");
    this->compute_centroids();
    fill_output();
    output.display("after");
    stop = (output-old_output)>tol;
  }
  std::cout << "the number of iterations is : " << iter << " and the signal stop is : " << stop << '\n';
}

// Private methods
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

/*
Fill the output image with the value corresponding
to the clusters associated with the pixel.
*/
template <typename T, typename Met>
void KMeans<T, Met>::fill_output() {
  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      for (size_t z = 0; z < depth; z++) {
        T min_dist = get_distance(0,x,y,z);
        output(x,y,z) = clusters[1];
        for (size_t i = 0; i < nb_clusters; i++) {
          T distance = get_distance(i,x,y,z);
          if (distance < min_dist) {
            min_dist = distance;
            output(x,y,z) = clusters[i+1];
          }
        }
      }
    }
  }
}

/*
Search the new centroids for the KMeans
algorithm.
*/
template <typename T, typename Met>
void KMeans<T, Met>::compute_centroids() {
}
