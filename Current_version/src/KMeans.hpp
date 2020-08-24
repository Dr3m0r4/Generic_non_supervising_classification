#ifndef KMEANS_HPP
#define KMEANS_HPP

#include "CImg.h"
#include "Computation.hpp"
#include "Descriptors.hpp"
#include "Metric.hpp"

/*
It is possible to do both : with and without executing the FCM.
You can have an exemple how to do it in the main.cpp file
*/
template <typename T>
void kmeans(
    /*
    input
    need to be initialised
    */
    const cimg_library::CImg<T>& desc,
    const cimg_library::CImg<int>& descInit,
    int nb_clusters,
    const int itermax,
    double tol,
    /*
    output
    */
    cimg_library::CImgList<T>& output,
    cimg_library::CImgList<T>& centroids = cimg_library::CImgList<T>::empty(),
    /*
    metrics
    */
    double (*metric)(
        const cimg_library::CImg<T>& a,
        const cimg_library::CImg<T>& b,
        ...
        /*
        matrix A that is the base of a A-norm if necessary
        */
    ) = &(Linf<T>),
    double (*stopMet)(
        const cimg_library::CImg<T>& a,
        const cimg_library::CImg<T>& b,
        ...
        /*
        matrix A that is the base of a A-norm
        */
    ) = &(L2<T>),
    /*
    functions
    */
    void (*update)(
        /*
        input
        */
        const cimg_library::CImg<T>& desc,
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
        m value first, then matrix A value if necessary
        */
    ) = &(FCMclusters<T>),
    void (*computeCenters)(
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
    ) = &(FCMcentroids<T>),
    /*
    Save
    */
    const char* save_name = "",
    cimg_library::CImgDisplay& kmeansDisp = cimg_library::CImgDisplay::empty(),
    /*
    Fuzzy
    allow to compute FCM algorithm and to have multiple images at the end
    */
    bool fuzzy = false,
    double m = 0,
    cimg_library::CImg<T> matA = cimg_library::CImg<T>::empty()
) {
    /*
    declaration of the variables
    */
    bool stop(false);
    int iter(0);
    int width(desc.width()), height(desc.height()), depth(desc.depth());
    double error;

    cimg_library::CImg<double> sum;
    /*
    Initialisation of the final image. If we are doing a fuzzy algorithm, we have nb_clusters images.
    */
    if (fuzzy) {
        output.assign(nb_clusters, width, height, depth, 1, 0);
    } else {
        output.assign(1, width, height, depth, 1, 0);
    }
    /*
    Matrix used for the computation of the final image.
    */
    cimg_library::CImgList<double> result(nb_clusters, width, height, depth, 1, 0);

    centroids.assign(nb_clusters, 1, desc.spectrum());
    cimg_library::CImgList<T> clusters(nb_clusters, 1);

    /*
    used for the fuzzy algorithm
    */
    if (matA.width() != descInit.height()) {
        matA = cimg_library::CImg<T>::identity_matrix(descInit.height());
    }

    /*
    initialisation of the centroids
    */
    cimg_forX(clusters,i) {
        clusters(i,0) = (T) (i+1)*255/nb_clusters;
        cimg_forY(descInit,j) {
            centroids(i,j) = (T) (descInit(j)>0?(rand() % descInit(j))*255/descInit(j):0);
        }
    }

    /*
    this line initialize the variable that will store the precedent value of the output
    */
    // cimg_library::CImgList<double> old_centroids(centroids);
    cimg_library::CImgList<T> old_output(output);

    /*
    Computation
    initialisation of the image
    */
    update(desc, centroids, metric, result, m, matA);
    while (!stop && iter < itermax && !(!kmeansDisp.is_empty() && kmeansDisp.is_closed())) {
        iter++;
        /*
        Research of the new centroids
        */
        computeCenters(desc, result, centroids, clusters, m);
        /*
        Completing the image with the new centroids
        */
        update(desc, centroids, metric, result, m, matA);
        if (fuzzy) {
            cimg_forX(output,i) {
                output(i) = (T) 255*result(i);
            }
        } else {
            output(0) = (T) 0;
            cimg_forX(result,c) {
                cimg_forXYZ(result(c),x,y,z) {
                    output(0,x,y,z) += result(c,x,y,z)*clusters(c,0);
                }
            }
        }

        /*
        computation of the error
        */
        sum.assign(output.width());
        cimg_forX(sum,i) {
            // sum(i) = stopMet(centroids(i), old_centroids(i));
            sum(i) = stopMet(output(i), old_output(i));
        }
        error = sum.max();
        if (error < tol) {
            stop = true;
        } else {
            old_output = output;
        }

        /*
        Displaying the result
        */
        if (!(kmeansDisp.is_empty())) {
            output.display(kmeansDisp);
        }

        /*
        Displaying the iteration
        */
        std::cout << "iteration " << iter << " with an error of " << error << '\n';
    }
    std::cout << "it ended at the iteration " << iter << " with an error of " << error << '\n';
    std::cout << "there is still " << centroids.size() << " clusters" << '\n';
    /*
    If there is a name, we are saving the different images produced.
    When the fuzzy algorithm is used, you will have nb_clusters images saved.
    Else you will have only one image saved.
    */
    if (strcmp(save_name,"")) {
        cimg_forX(output,i) {
            output(i).save(save_name,i,3);
        }
    }
}

/*
The vectors should be vertical : CImg<T>(1,n) where n is the size of the vector.
*/

/*
I offer the possibility to do some metrics with a function. The prototype should be like this :
template <typename T>
double metric (CImg<T> a, CImg<T> b, ...);
I use a variadic if we need some complementary information like a matrix
*/

/*
The descriptors desc, should be a CImg image. The three first dimensions are the same than the original image. The last one (spectrum) contains the descriptor vector.
To access to the vector, you can use the methods get_vector_at(x,y,z)
*/

#endif
