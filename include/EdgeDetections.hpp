#pragma once

#include "BinaryGray.hpp"

struct Gradient
{
    GrayscaleImage magnitude;
    GrayscaleImage direction;
};

GrayscaleImage meanBlur(const GrayscaleImage &img);

Matrix getGaussianKernel(int size, double sigma);

void applyKernel(const GrayscaleImage &image, Matrix &mkernel, GrayscaleImage &output);

GrayscaleImage applyGaussian(const GrayscaleImage &image, int size, double sigma);

GrayscaleImage robertsCross(const GrayscaleImage &image);

Gradient prewitt(const GrayscaleImage &img);

GrayscaleImage simpleGaussianBlur(const GrayscaleImage &image);