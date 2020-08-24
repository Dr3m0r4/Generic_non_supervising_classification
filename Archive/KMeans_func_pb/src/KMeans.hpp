#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "CImg.h"

template <typename T> // the typename Met should be a Metric
void kmeans(
  // input
    // need to be initialised
  const cimg_library::CImg<cimg_library::CImg<T>>& desc,
  int nb_clusters,
  const int itermax,
  double tol,
  void (*computeImage)(
    // input
    const cimg_library::CImg<cimg_library::CImg<T>>& desc,
    cimg_library::CImgList<T>& clusters,
    cimg_library::CImgList<T>& centroids,
    // output
    cimg_library::CImg<T>& output,
    cimg_library::CImg<cimg_library::CImgList<T>>& pixels,
    // metrics
    double (*met)(
      cimg_library::CImg<T> a,
      cimg_library::CImg<T> b
    )
  ),
  void (*computeCenters)(
    // input
    cimg_library::CImg<cimg_library::CImgList<T>>& pixels,
    cimg_library::CImgList<T>& centroids,
    // output
    cimg_library::CImgList<T>& old_centr,
    cimg_library::CImgList<T>& clusters
  ),
  // output
  cimg_library::CImg<T>& result,
  cimg_library::CImgList<T>& centroids, // the shape will be [nb_clusters][desc.getDim()]
  // metrics
  double (*stopMet)(
    // stop function under convergence criteria
    // should be a metric
    cimg_library::CImg<T> a,
    cimg_library::CImg<T> b
  ),
  double (*metric)(
    cimg_library::CImg<T> a,
    cimg_library::CImg<T> b
  ),
  // Display
  bool display = false,
  const char* save_name = ""
) {
  // initialisation of the variables
  bool stop(false);
  int iter(0);
  cimg_library::CImgList<T> old_centroids;
  int width(desc.width()), height(desc.height()), depth(desc.depth()), spectrum(desc.spectrum());
  result.assign(cimg_library::CImg<T>(width, height, depth, 1, 0));
  centroids = cimg_library::CImgList<T>(nb_clusters);
  cimg_library::CImgList<T> clusters(nb_clusters,1);
  cimg_library::CImg<cimg_library::CImgList<T>> pixels(nb_clusters);
  cimg_library::CImg<T> sum;
  double error;
  cimg_library::CImgDisplay kmeansDisp(result);
  // this part could replace by initialising each member of the centroids independantly within the bounds
  // like (T) (rand() % width);
  // the value of the pixel should be the last value of the descriptor
  // Still have to modify this part to get a generic function possible with different descriptors
  for (size_t i = 0; i < nb_clusters; i++) {
    clusters(i,0)   = (T) (i+1)*255/nb_clusters;
    centroids(i)    = cimg_library::CImg<T>(4);
    centroids(i)(0) = (T) (rand() % desc.width());
    centroids(i)(1) = (T) (rand() % desc.height());
    centroids(i)(2) = (T) (rand() % desc.depth());
    centroids(i)(3) = (T) (rand() % 255);
  }

  if (display) {
    kmeansDisp = result;
  } else {
    kmeansDisp = cimg_library::CImgDisplay::empty();
  }

  // Computation
  computeImage(desc, clusters, centroids, result, pixels, metric);
  while (!stop && iter < itermax && !(display && kmeansDisp.is_closed())) {
    iter++;
    old_centroids = centroids;
    computeCenters(pixels, centroids, old_centroids, clusters);
    computeImage(desc, clusters, centroids, result, pixels, metric);
    sum = cimg_library::CImg<T>(centroids.size());
    for (size_t i = 0; i < centroids.size(); i++) {
      sum(i) = stopMet(centroids(i), old_centroids(i));
    }
    if (display) {
      result.display(kmeansDisp);
    }
    // error = sqrt(sum.sum());
    error = sum.max();
    if ( error < tol) {
      stop = true;
    }
    std::cout << "iteration " << iter << " with an error of " << error << '\n';
  }
  std::cout << "it ended at the iteration " << iter << " with an error of " << error << '\n';
  std::cout << "there is still " << centroids.size() << " clusters" << '\n';
  if (save_name != "") {
    result.save_png(save_name);
  }
}

/*
to obtain a good Metric evaluator, you should use this model
it should be a fonctor that will evaluate the distance between 1 vector from the descriptor and the centroid

the prototype should be like this :
template <typename T>
double metric (CImg<T> a, CImg<T> b);
*/

/*
The descriptors desc, should be some CImgList images. They are vectors.
For the simple one, there is 4 value : the 3 dimensions and the pixel's value
*/

#endif
