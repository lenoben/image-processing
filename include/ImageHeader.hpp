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
#include <algorithm>
#include <utility>
#include <stack>
#include <unordered_set>
#include <unordered_map>

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

struct cmyk
{
    double c;
    double m;
    double y;
    double k;
};

typedef std::vector<cmyk> CmykArray;
typedef std::vector<CmykArray> CmykMatrix;

#endif