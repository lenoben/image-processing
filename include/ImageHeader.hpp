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

struct hsi
{
    double h;
    double s;
    double i;
};

typedef std::vector<hsi> HsiArray;
typedef std::vector<HsiArray> HsiMatrix;

struct hsl
{
    double h;
    double s;
    double l;
};

typedef std::vector<hsl> HslArray;
typedef std::vector<HslArray> HslMatrix;

// x and y
typedef std::pair<int, int> pixelcoordinate;
// label with pixels x and y
typedef std::pair<int, pixelcoordinate> label_und_pixel;

struct Moments
{
    double M00 = 0.0;
    double M10 = 0.0;
    double M01 = 0.0;
};
#endif