#pragma once

#include "BinaryGray.hpp"

struct Gradient
{
    GrayscaleImage magnitude;
    GrayscaleImage direction;
};

GrayscaleImage meanBlur(const GrayscaleImage &img);

Matrix getGaussianKernel(int size = 5, double sigma = 1.0);

void applyKernel(const GrayscaleImage &image, Matrix &mkernel, GrayscaleImage &output);

GrayscaleImage applyGaussian(const GrayscaleImage &image, int size = 3, double sigma = 1.0);

GrayscaleImage robertsCross(const GrayscaleImage &image);

Gradient prewitt(const GrayscaleImage &img);

GrayscaleImage simpleGaussianBlur(const GrayscaleImage &image);

Gradient sobel(const GrayscaleImage &image);

GrayscaleImage nonMaximumSuppression(const GrayscaleImage &magnitude, const GrayscaleImage &direction);

GrayscaleImage doubleThreshold(const GrayscaleImage &image, int lowThreshold, int highThreshold);

void edgeTrackingByHysteresis(GrayscaleImage &image);

GrayscaleImage cannyEdgeDetection(const GrayscaleImage &image, int lowThreshold = 50, int highThreshold = 150);