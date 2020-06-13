// Constructors
template <typename T, typename Met>
KMeans<T, Met>::KMeans(cimg_library::CImg<T> image, int nb_c, size_t itermax) {
  img.assign(cimg_library::CImg<T>(image));
  nb_clusters = nb_c;
  width = img.width(); height = img.height(); depth = img.depth();
  spectrum = img.spectrum();
  // centroids = new int*[nb_clusters];
  // clusters = new T[nb_clusters+1];
  vect_p = new std::vector<Pixel<T>>[nb_clusters];

  output.assign(cimg_library::CImg<T>(width,height,depth,1,0));
  // clusters[0] = 0;
  clusters.push_back(0);
  for (size_t i = 0; i < nb_clusters; i++) {
    // clusters[i+1] = (i+1)*max_value/(nb_clusters+1);
    // centroids[i] = new int[3];
    clusters.push_back((i+1)*max_value/(nb_clusters+1));
    centroids.push_back(Pixel<T>(
      (T) (rand() % width),
      (T) (rand() % height),
      (T) (rand() % depth),
      (T) (rand() % (int)max_value)
    ));
    // centroids.push_back(new T[4]);
    // centroids[i][0] = (T) (rand() % width);
    // centroids[i][1] = (T) (rand() % height);
    // centroids[i][2] = (T) (rand() % depth);
    // centroids[i][3] = (T) (rand() % (int)max_value);
  }

  this->max_iter = itermax;
}

// Display
template <typename T, typename Met>
void KMeans<T, Met>::display_centroids() const {
  for (size_t i = 0; i < nb_clusters; i++) {
    std::cout << "centroid " << i << " x : " << centroids[i][0] << " | y : " << centroids[i][1] << " | z : " << centroids[i][2] << " | value : " << centroids[i][3] << '\n';
  }
  std::cout << '\n';
}

template <typename T, typename Met>
void KMeans<T, Met>::display_centroids(int i) const {
  std::cout << "centroid " << i << " x : " << centroids[i][0] << " | y : " << centroids[i][1] << " | z : " << centroids[i][2] << " | value : " << centroids[i][3] << '\n';
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

  T result(0);
  Pixel<T> inter(x, y, z, img(x,y,z));

  result = Met()(centroids[i], inter);

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
  int** old_centr = fill_centroids();
  // cimg_library::CImg<T>* old_output = new cimg_library::CImg<T>(output);
  fill_output();
  // output.display("iteration 0");
  output.save_png("../images/before.png");
  // bool stop(compare_centroids(diff_centroids(old_centr), tol));
  double diff(diff_centroids(old_centr));
  double old_diff(1.0), error(1);
  bool stop(error < tol);
  while (iter < max_iter && !stop) {
    iter++;
    std::cout << "start of iteration " << iter << '\n';
    // old_output = new cimg_library::CImg<T>(output);
    // display_centroids();
    old_diff = diff;
    old_centr = fill_centroids();
    this->compute_centroids();
    this->fill_output();
    // output.display("iteration "+char(iter));
    // display_centroids();
    // stop = compare_centroids(diff_centroids(old_centr), tol);
    diff = diff_centroids(old_centr);
    error = std::abs(old_diff-diff);
    stop = error < tol;
    std::cout << ">>> iteration " << iter << " with an error of " << error << '\n';
  }
  std::cout << "the number of iterations is : " << iter << " and the difference is : " << diff << '\n';
  std::cout << "the number of clusters is " << nb_clusters << '\n';
  // output.display("end of the algorithm");
  output.save_png("../images/after.png");
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
        for (size_t i = 0; i < nb_clusters; i++) {
          if (output(x,y,z) == clusters[i+1]) {
            vect_p[i].push_back(Pixel<T>(x,y,z,img(x,y,z)));
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
  Pixel<T> p(0,0,0,0);
  T* sum = new T[4];
  size_t size(0);
  bool suppr(false);
  for (size_t i = 0; i < nb_clusters; i++) {
    for (size_t j = 0; j < 3; j++) {
      sum[j] = 0;
    }
    // std::cout << "start of centroid " << i << '\n';
    size = vect_p[i].size();
    if (size) {
      while (!vect_p[i].empty()) {
        p = vect_p[i].back();
        sum[0] += p.getX();
        sum[1] += p.getY();
        sum[2] += p.getZ();
        sum[3] += p.getV();
        vect_p[i].pop_back();
      }
      // std::cout << "end of centroid " << i << '\n';
      for (size_t j = 0; j < 4; j++) {
        centroids[i][j] = sum[j]/size;
      }
    } else if (!suppr) {
      // std::cout << "tes baise" << '\n';
      centroids.erase(centroids.begin()+i);
      clusters.erase(clusters.begin()+i+1);
      nb_clusters--;
      i--;
      suppr = true;
    }
  }
}

template <typename T, typename Met>
int** KMeans<T, Met>::fill_centroids() {
  int** result = new int*[nb_clusters];
  for (size_t i = 0; i < nb_clusters; i++) {
    result[i] = new int[3];
    for (size_t j = 0; j < 3; j++) {
      result[i][j] = centroids[i][j];
    }
  }
  return result;
}

// #include <cmath>
template <typename T, typename Met>
double KMeans<T, Met>::diff_centroids(int** old_centr) {
  // double** result = new double*[nb_clusters];
  double result(0);
  for (size_t i = 0; i < nb_clusters; i++) {
    // result[i] = new double[3];
    for (size_t j = 0; j < 3; j++) {
      // result[i][j] = abs(centroids[i][j]-old_centr[i][j]);
      result += std::pow(centroids[i][j]-old_centr[i][j],2);
    }
  }
  return std::sqrt(result);
}

template <typename T, typename Met>
bool KMeans<T, Met>::compare_centroids(double** diff, double tol) {
  bool result(false);
  for (size_t i = 0; i < nb_clusters; i++) {
    for (size_t j = 0; j < 3; j++) {
      result = result && diff[i][j]<tol;
    }
  }
  return result;
}
