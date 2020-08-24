#ifndef COMPUTATION_HPP
#define COMPUTATION_HPP

#include "CImg.h"

/*
proposition of completing an image
*/
template <typename T>
void researchClusters(
    /*
    input
    */
    const cimg_library::CImg<T>& DescGen,
    const cimg_library::CImgList<T>& centroids,
    /*
    metrics
    */
    double (*met)(
        const cimg_library::CImg<T>& a,
        const cimg_library::CImg<T>& b,
        ...
        /*
        matrix A that is the base of a A-norm
        */
    ),
    /*
    output
    */
    cimg_library::CImgList<double>& output,
    double m,
    cimg_library::CImg<T> matA
) {
    double min_dist, distance;
    int prec_min(0);
    cimg_library::CImg<T> desc(1,DescGen.spectrum()), centroid(1,DescGen.spectrum());
    cimg_forXYZ(DescGen,x,y,z){
        desc = DescGen.get_vector_at(x,y,z);
        centroid = centroids(0);
        min_dist = met(desc,centroid,matA);
        cimg_forX(output,i) {
            output(i,x,y,z) = 0;
        }
        output(0,x,y,z) = 1;
        prec_min = 0;
        cimg_forX(centroids,i) {
            centroid = centroids(i);
            distance = met(desc,centroid,matA);
            if (distance < min_dist) {
                min_dist = distance;
                output(prec_min,x,y,z) = 0;
                output(i,x,y,z) = 1;
                prec_min = i;
            }
        }
    }
}

/*
proposition of seeking the centroids
*/
template <typename T>
void searchCentroids(
    /*
    input
    */
    const cimg_library::CImg<T>& desc,
    const cimg_library::CImgList<double>& output,
    cimg_library::CImgList<T>& centroids,
    cimg_library::CImgList<T>& clusters,
    double m
    /*
    m value first, then matrix A value if necessary
    */
) {
    int size_p(desc.spectrum()), nb_clusters(centroids.width()); double size(0);

    cimg_library::CImg<double> sum(1,size_p);

    cimg_forX(centroids,c) {
        sum = (double) 0;
        size = 0;
        cimg_forXYZ(desc,x,y,z) {
            sum += output(c,x,y,z)*desc.get_vector_at(x,y,z);
        }
        size = output(c).sum();
        if (size > 0) {
            centroids(c) = sum/size;
        }
    }
}

/*
FCM Computation
*/
template <typename T>
void FCMclusters(
    /*
    input
    */
    const cimg_library::CImg<T>& DescGen,
    const cimg_library::CImgList<T>& centroids,
    /*
    metrics
    */
    double (*met)(
        const cimg_library::CImg<T>& a,
        const cimg_library::CImg<T>& b,
        ...
        /*
        matrix A that is the base of a A-norm
        */
    ),
    /*
    output
    */
    cimg_library::CImgList<double>& output,
    double m,
    cimg_library::CImg<T> matA
    /*
    m value first, then matrix A value
    m should be between 1.5 and 3.0
    */
) {
    double distance, sum(0);
    cimg_library::CImg<T> desc(1,DescGen.spectrum()), centroid(1,DescGen.spectrum());
    cimg_library::CImg<double> Distances(1,centroids.size());

    cimg_forXYZ(DescGen,x,y,z){
        desc = DescGen.get_vector_at(x,y,z);
        /*
        necessity for the initialisation
        the use of a CImg variable will cause a SIGSEV error. You need to initialize the variable at each iteration to avoid this problem.
        */
        Distances = (double) 0;
        cimg_forX(centroids,i) {
            centroid = centroids(i);
            distance = met(desc,centroid,matA);
            Distances(i) = distance;
        }
        cimg_forY(Distances,i) {
            sum = 0;
            cimg_forY(Distances,j) {
                sum += pow(Distances(i)/Distances(j),2/(m-1));
            }
            output(i,x,y,z) = 1/sum;
        }
    }
    /*
    Verification that the output is well built
    */
    cimg_library::CImg<double> res = output > 'c';
    double verif = 0;
    cimg_forXYZ(res,x,y,z){
        verif = res.get_vector_at(x,y,z).sum();
        if ( verif < 0.99 || verif > 1+1e-8 ) {
            throw cimg_library::CImgAbortException("bad computation : %.1f",verif);
        }
    }
}

template <typename T>
void FCMcentroids (
    /*
    input
    */
    const cimg_library::CImg<T>& desc,
    const cimg_library::CImgList<double>& output,
    cimg_library::CImgList<T>& centroids,
    cimg_library::CImgList<T>& clusters,
    double m
    /*
    m value first, then matrix A value if necessary
    */
) {
    int size_p(desc.spectrum()), nb_clusters(centroids.width());
    double size(0);

    cimg_library::CImg<double> sum(1,size_p);
    cimg_library::CImg<double> wei(desc,"x,y,z,1");

    cimg_forX(centroids,c) {
        sum = (double) 0;
        size = 0;
        wei = output(c).get_pow(m);
        size += wei.sum();
        cimg_forXYZ(desc,x,y,z) {
            sum += wei(x,y,z)*desc.get_vector_at(x,y,z);
        }
        if (size > 0) {
            centroids(c) = sum/size;
        }
    }
}

template <typename T>
cimg_library::CImg<T> synthesis(
    cimg_library::CImgList<T> list_clust
) {
    int nb_clusters = list_clust.size();
    int x_max, y_max, z_max;

    cimg_library::CImg<T> clusters = list_clust>'c';
    cimg_library::CImg<T> res(clusters,"x,y,z,1");
    cimg_library::CImg<T> proba(nb_clusters);
    cimg_library::CImg<T> colors(nb_clusters);

    cimg_forX(colors,i) {
        colors(i) = (T) (i+1)*255/nb_clusters;
    }

    cimg_forXYZ(res,x,y,z) {
        proba = clusters.get_vector_at(x,y,z);
        if (proba.contains(proba.max(),x_max,y_max,z_max)) {
            res(x,y,z) = colors(proba.offset(x_max,y_max,z_max));
        }
    }

    return res;
}

#endif
