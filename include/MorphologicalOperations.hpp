#pragma once

#include "BinaryGray.hpp"

void printMatrix(IntMatrix &Tmatrix);

IntMatrix flipXY(IntMatrix Tmatrix);

BinaryGrayImage Dilation(const BinaryGrayImage &img, IntMatrix kernel);