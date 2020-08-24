#ifndef DESCRIPTORS_HPP
#define DESCRIPTORS_HPP

#include "CImg.h"
#include "Metric.hpp"

template <typename T>
cimg_library::CImg<T> greyscale(const cimg_library::CImg<T>& img) {
    cimg_library::CImg<T> grey(img,"x,y,z,1");
    cimg_forXYZ(img,x,y,z) {
        grey(x,y,z) = img.get_vector_at(x,y,z).mean();
    }
    return grey;
}

/*
Represents all the features you can have whithin the descriptors builder
If you want to add features, you should do it before the MaxSize value
*/
enum desc_type : int {
    Width_desc = 0,
    Height_desc,
    Depth_desc,
    Red,
    Green,
    Blue,
    Grey,
    Grad_x,
    Grad_y,
    Grad_z,
    Hue,
    Saturation,
    Luminosity,
    MaxSize
};

/*
Help you to build a CImg variable that will be used to choose which feature you will use
You can use the desc_type enum to indicate the index
*/
cimg_library::CImg<bool> choice_descriptors(int nb_feat, ...) {
    va_list args;
    cimg_library::CImg<bool> res(1,desc_type::MaxSize,1,1,false);
    va_start(args,nb_feat);
    int cpt(0), indx;

    while (cpt<nb_feat && cpt<desc_type::MaxSize) {
        indx = va_arg(args, int);
        if (indx < desc_type::MaxSize)
            res(indx) = true;
        cpt++;
    }
    va_end(args);

    return res;
}

/*
Propose a method to build a descriptor for the Kmeans algorithm. This descriptor could be use for another method.
*/
template <typename T>
void descriptor(
    /*
    Essential
    */
    const cimg_library::CImg<T>& img,
    cimg_library::CImg<T>& result,
    cimg_library::CImg<int>& init,
    /*
    Optionnal
    */
    cimg_library::CImg<bool> choice = cimg_library::CImg<bool>::empty()
) {
    char dim[30], dimMax[30];

    /*
    Determining if the choice of the features is well made
    Else, all the disposable features will be chosen
    */
    if (choice.is_empty() || choice.size() != desc_type::MaxSize) {
        std::cout << "\nWarning : The choice vector wasn't correct. We are using all the parameters." << std::endl;
        choice = cimg_library::CImg<bool>(1, desc_type::MaxSize);
        choice = true;
    }

    int size = 0;
    cimg_forY(choice,x) {
        size += choice(x)?1:0;
    }

    /*
    initialisation of the variables
    */
    sprintf(dim,"x,y,z,%d",size);
    sprintf(dimMax,"x,y,z,%d",desc_type::MaxSize);
    cimg_library::CImg<T> desc(img,dimMax);
    cimg_library::CImgList<T> gradient = img.get_gradient();
    cimg_library::CImg<int> refInit(1, desc_type::MaxSize);
    cimg_library::CImg<T> img_hsl = img.get_RGBtoHSL();
    cimg_library::CImgList<T> list_hsl = img_hsl < 'c';
    result.assign(img,dim);
    init.assign(1,size);

    /*
    initialisation of the maxima values
    */
    refInit(desc_type::Width_desc) = img.width();
    refInit(desc_type::Height_desc) = img.height();
    refInit(desc_type::Depth_desc) = img.depth();
    refInit(desc_type::Red) = (int) img.max()+1;
    refInit(desc_type::Green) = (int) img.max()+1;
    refInit(desc_type::Blue) = (int) img.max()+1;
    refInit(desc_type::Grey) = (int) img.max()+1;
    refInit(desc_type::Grad_x) = (int) gradient(0).max()+1;
    refInit(desc_type::Grad_y) = (int) gradient(1).max()+1;
    refInit(desc_type::Grad_z) = (int) gradient.size()>2?gradient(2).max()+1:0;
    refInit(desc_type::Hue) = (int) list_hsl(0).max()+1;
    refInit(desc_type::Saturation) = (int) list_hsl(1).max()+1;
    refInit(desc_type::Luminosity) = (int) list_hsl(2).max()+1;

    /*
    Affectation to the init variable all the chosen maxima features
    */
    for(int i=0,j=0; i<size && j<desc_type::MaxSize; ++i, ++j) {
        if (choice(j)) {
            init(i) = refInit(j);
        } else {
            --i;
        }
    }

    /*
    Filling the general descriptor
    The image should be in RGB
    */
    int count(0);
    cimg_forXYZ(img,x,y,z){
        count = 0;
        /*
        All the coordinates
        */
        desc(x,y,z,count++) = (T) x;
        desc(x,y,z,count++) = (T) y;
        desc(x,y,z,count++) = (T) z;
        /*
        The image should be in RGB for the next lines
        */
        cimg_forC(img,c) {
            desc(x,y,z,count+c) = (T) img(x,y,z,c);
        }
        count += img.spectrum();
        desc(x,y,z,count++) = img.get_vector_at(x,y,z).mean();
        cimg_forX(gradient,i) {
            desc(x,y,z,count+i) = gradient(i,x,y,z);
        }
        count += gradient.size()<3?3:gradient.size();
        cimg_forC(img_hsl,c) {
            desc(x,y,z,count+c) = img_hsl(x,y,z,c);
        }
        count += img_hsl.spectrum();

        while (count < desc_type::MaxSize) {
            desc(x,y,z,count++) = 0;
        }

        /*
        choosing the parameter we want
        */
        for(int i=0,j=0; i<size && j<desc_type::MaxSize; ++i, ++j) {
            if (choice(j)) {
                result(x,y,z,i) = refInit(j)?desc(x,y,z,j)*255/refInit(j):0;
            } else {
                --i;
            }
        }
    }
}

#endif
