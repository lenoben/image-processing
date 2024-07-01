#pragma once

#include "BinaryGray.hpp"

GrayscaleImage meanBlur(const GrayscaleImage &img);

Matrix getGaussianKernel(int size, double sigma);

void applyKernel(const GrayscaleImage &image, Matrix &mkernel, GrayscaleImage &output);

GrayscaleImage applyGaussian(const GrayscaleImage &image, int size, double sigma);