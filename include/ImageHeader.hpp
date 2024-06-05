#ifndef _LIB_IMAGE_HEADER_HPP
#define _LIB_IMAGE_HEADER_HPP

#include "Image.h"
#include <vector>
#include <tuple>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <math.h>

typedef std::vector<double> Array;
typedef std::vector<Array> Matrix;

typedef std::vector<int> IntArray;
typedef std::vector<IntArray> IntMatrix;

struct pixel
{
    int r;
    int g;
    int b;
};

typedef std::vector<pixel> PixelArray;
typedef std::vector<PixelArray> PixelMatrix;

struct hsv
{
    double h;
    double s;
    double v;
};

typedef std::vector<hsv> HsvArray;
typedef std::vector<HsvArray> HsvMatrix;

#endif