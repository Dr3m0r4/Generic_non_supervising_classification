#include <iostream>

#include "KMeans.hpp"

using namespace cimg_library;

/*
Currently, there is no possibility to use any other type than the double. I will take a thought about it a little further.
*/
using T = double;

int main(int argc, char const *argv[]) {

    /*
    random initialisation
    If you want to have a deterministic system, you should comment this line
    */
    // srand(time(NULL));
    /*
    The name is thought as a linux name. You should change it if you are on another OS.
    */
    std::string name, path_name("../images/"), final_name("result_");
    int nb_clusters, max_iter(10000);
    /*
    m is the weight pushed on the centroids
    */
    double m(1.5);
    /*
    tol is the convergence limit
    */
    double tol(1e-4);
    bool fuzzy(true);
    /*
    It represents the number of variable within the descriptor
    */
    int nb_features(4);
    /*
    If you want to enter the name of the image and the number of the clusters at each time you run the program, change the value to true
    */
    const bool choice(false);
    if (choice) {
        std::cout << "Enter the name of the image you want to analyse :" << '\n';
        std::cin >> name;
        std::cout << "Enter the number of clusters you want to determine :" << '\n';
        std::cin >> nb_clusters;
    } else {
        /*
        Else you can directly change the values here but you'll need to compile the program again
        */
        nb_clusters = 5;
        name = "test.jpeg";
    }

    /*
    Loading the image
    */
    CImg<T> image((path_name+name).c_str());
    /*
    Turning it to a grey image
    */
    // CImg<T> greyImg(greyscale(image));

    /*
    Initialising a new display variable
    */
    CImgDisplay mainDisp(image,"Main Display");
    image.display(mainDisp);

    /*
    We are creating here the descriptor.
    */
    CImg<bool> descChoice = choice_descriptors( nb_features, desc_type::Width_desc, desc_type::Height_desc, desc_type::Depth_desc, desc_type::Luminosity, desc_type::Grey, desc_type::Grad_x, desc_type::Grad_y);

    CImg<T> desc;
    CImg<int> init;
    /*
    Line used to create the descriptor
    */
    descriptor(image, desc, init, descChoice);

    /*
    Proposition of a matrix for A_norm
    You should build your own A matrix.
    The dimensions should be (desc.spectrum())² for the computation.
    */
    CImg<T> matA(desc.spectrum(),desc.spectrum());
    cimg_forY(matA,y) {
        cimg_forX(matA,x) {
            matA(x,y) = 4;
        }
        matA(matA.width()-1,y) = 0;
    }
    cimg_forX(matA,x) {
        matA(x,matA.height()-1) = 0;
    }
    matA(matA.width()-1,matA.height()-1) = 1;

    /*
    Creating the output list of images
    */
    CImgList<T> result;
    CImgList<T> centroids;
    std::string end_name = path_name+final_name+std::to_string(nb_clusters)+(fuzzy?"_fuzzy_":"_")+name;
    /*
    Creating an empty instance of a display to avoid diplaying during the computation
    If you are using the fuzzy algorithm, the display is considered as void
    */
    // CImgDisplay empt = CImgDisplay::empty();

    CImg<T> a(1,1,1,1,0), b(1,1,1,1,1);
    std::cout << Linf(a,b) << '\n';

    /*
    Computing the Kmeans algorithm
    */
    kmeans<T>(
        /*
        The descriptor and the init maxima.
        You can build it with the descriptor function
        */
        desc,
        init,
        /*
        The number of cluster you want to identify
        */
        nb_clusters,
        /*
        The maximum number of iterations and the tolerance to stop the algorithm
        */
        max_iter,
        tol,
        /*
        The final result and the centroids
        */
        result,
        centroids,
        /*
        The metric used for the computation
        */
        &Linf<T>,
        /*
        The metric used for the stop condition
        The algorithm is not ready for a A_norm metric as stop condition
        */
        &L2<T>,
        /*
        Function to compute the new image
        */
        fuzzy?&(FCMclusters<T>):&(researchClusters<T>),
        /*
        Function to determine the new position of the centers
        */
        fuzzy?&(FCMcentroids<T>):&(searchCentroids<T>),
        /*
        Name of the images output. You need only one name.
        If the name is "" you won't save any images.
        You should use a char* as a name.
        */
        end_name.c_str(),
        /*
        CImgDisplay chose for displaying, if empty there will be no display
        */
        mainDisp,
        /*
        Boolean allowing to have multiple images at the end
        */
        fuzzy,
        /*
        Weight used for the fuzzy algorithm
        */
        m,
        /*
        Matrix to use with a metric
        */
        matA
    );

    CImg<T> res_fuzz = CImg<T>::empty();
    if (fuzzy) {
        std::cout << "number of clusters : " << result.size() << '\n';
        res_fuzz = synthesis(result);
        res_fuzz.save(end_name.insert(end_name.find_last_of("."),"_final").c_str());
    }

    // Displaying the result seeked at the end of the computation
    (result,res_fuzz).display("Final Result");

    return 0;
}
