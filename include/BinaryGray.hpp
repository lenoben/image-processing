#ifndef _LIB_BINARY_GRAY
#define _LIB_BINARY_GRAY

#include "ImageHeader.hpp"

class BinaryGrayImage
{
    IntMatrix matrix;

public:
    int width;
    int height;

public:
    BinaryGrayImage(){};

    BinaryGrayImage(const BinaryGrayImage &other);

    BinaryGrayImage(int width, int height);

    BinaryGrayImage(IntMatrix &tmatrix);

    int operator()(int x_width, int y_height) const;

    int &operator()(int x_width, int y_height);
};

#endif