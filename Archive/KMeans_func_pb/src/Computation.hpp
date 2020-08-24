#ifndef COMPUTATION_HPP
#define COMPUTATION_HPP

#include "CImg.h"

template <typename T>
void researchClusters(
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
) {
  T min_dist, distance;
  int width(desc.width()), height(desc.height()), depth(desc.depth()), nb_clusters(centroids.size());
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      for (int z = 0; z < depth; z++) {
        min_dist = met(desc(x,y,z),centroids(0));
        output(x,y,z) = clusters(0,0);
        for (size_t i = 0; i < nb_clusters; i++) {
          distance = met(desc(x,y,z),centroids(i));
          if (distance < min_dist) {
           min_dist = distance;
           output(x,y,z) = clusters(i,0);
          }
        }
        for (size_t i = 0; i < nb_clusters; i++) {
          if (output(x,y,z) == clusters(i,0)) {
            pixels(i).push_back(desc(x,y,z));
          }
        }
      }
    }
  }
}

template <typename T>
void searchCentroids(
  // input
  cimg_library::CImg<cimg_library::CImgList<T>>& pixels,
  cimg_library::CImgList<T>& centroids,
  // output
  cimg_library::CImgList<T>& old_centr,
  cimg_library::CImgList<T>& clusters
) {
  int size_p(centroids(0).size());
  cimg_library::CImg<T> p(size_p), sum(size_p);
  int size(0), nb_clusters(centroids.size());
  bool suppr(true);
  for (size_t i = 0; i < nb_clusters; i++) {
    for (size_t j = 0; j < size_p; j++) {
      sum(j) = 0;
    }
    size = pixels(i).size();
    if (size) {
      while (!pixels(i).is_empty()) {
        p = pixels(i).back();
        for (size_t j = 0; j < size_p; j++) {
          sum(j) += p(j);
        }
        pixels(i).pop_back();
      }
      centroids(i) = sum/size;
    } else if (suppr) {
      old_centr.erase(old_centr.begin()+i);
      centroids.erase(centroids.begin()+i);
      clusters.erase(clusters.begin()+i);
      nb_clusters--;
      i--;
      suppr = false;
    }
  }
}

#endif
