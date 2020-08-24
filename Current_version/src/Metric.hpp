#ifndef METRIC_HPP
#define METRIC_HPP

#include "CImg.h"

/*
to obtain a good Metric, you should use this model
*/
template <typename T>
double Linf(
    const cimg_library::CImg<T>& a,
    const cimg_library::CImg<T>& b = cimg_library::CImg<T>::empty(),
    ...
) {
    if (!b.is_empty() && a.size() != b.size()) {
        throw cimg_library::CImgAbortException("The images have not the same dimensions");
    }
    double result(0);
    result = (a-b).abs().max();

    return result;
}

template <typename T>
double L2(
    const cimg_library::CImg<T>& a,
    const cimg_library::CImg<T>& b = cimg_library::CImg<T>::empty(),
    ...
) {
    if (!b.is_empty() && a.size() != b.size()) {
        throw cimg_library::CImgAbortException("The images have not the same dimensions");
    }
    double result(0);
    result = sqrt((a-b).sqr().sum());

    return result;
}

/*
FCM Metrics
*/
template <typename T>
double A_scalar(
    cimg_library::CImg<T> a,
    cimg_library::CImg<T> b,
    cimg_library::CImg<T> A = cimg_library::CImg<T>::empty()
) {
    if (a.height() != b.height()) {
        throw cimg_library::CImgArgumentException("The two vector doesn't have the same dimensions");
    }
    if (A.is_empty() || A.height()!=a.height() || A.width() != b.height()) {
        cimg_library::cimg::warn("The weight matrix isn't valid. The identity matrix will be used.");
        A = cimg_library::CImg<T>::identity_matrix(a.height());
    }
    double result = (a.transpose()*A*b)(0);
    return result;
}

template <typename T>
double A_norm(
    const cimg_library::CImg<T>& a,
    const cimg_library::CImg<T>& b = cimg_library::CImg<T>::empty(),
    ...
    /*
    The matrix A that is the base for this metric
    */
) {
    if (!b.is_empty() && a.size() != b.size()) {
        throw cimg_library::CImgAbortException("The images have not the same dimensions");
    }
    va_list args;
    va_start(args,b);
    cimg_library::CImg<T> A = va_arg(args,cimg_library::CImg<T>);
    va_end(args);
    return sqrt(A_scalar(a-b,a-b,A));
}

#endif
