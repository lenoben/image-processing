#pragma once

#include "BinaryGray.hpp"

void printMatrix(IntMatrix &Tmatrix);

IntMatrix flipXY(IntMatrix Tmatrix);

/**
 * @brief Performs the dilation transformation on the matrix on the BinaryGray class
 * @note: its expands the matrix
 *
 * @param img
 * @param kernel
 * @return BinaryGrayImage
 */
BinaryGrayImage Dilation(const BinaryGrayImage &img, IntMatrix kernel);

bool erods(bool kernel, bool img);

/**
 * @brief Performs the erosion transformation on the matrix
 *
 * @param img
 * @param kernel
 * @return BinaryGrayImage
 */
BinaryGrayImage Erosion(const BinaryGrayImage &img, IntMatrix kernel);