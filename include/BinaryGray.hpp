#ifndef _LIB_BINARY_GRAY
#define _LIB_BINARY_GRAY

#include "ImageHeader.hpp"

class BinaryGrayImage
{
    IntMatrix matrix;

public:
    int width;
    int height;
    float th; // threshold

public:
    BinaryGrayImage(){};

    BinaryGrayImage(const BinaryGrayImage &other);

    BinaryGrayImage(int width, int height);

    BinaryGrayImage(int width, int height, float tth);

    BinaryGrayImage(IntMatrix &tmatrix);

    void Load(GrayscaleImage &img, bool adaptativeThreshold = true, float manualThreshold = 128);

    int operator()(int x_width, int y_height) const;

    int &operator()(int x_width, int y_height);

    void inverse();
};

#endif