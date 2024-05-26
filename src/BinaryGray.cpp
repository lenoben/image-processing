#include "BinaryGray.hpp"

BinaryGrayImage::BinaryGrayImage(const BinaryGrayImage &other) : matrix(other.matrix), width(other.width), height(other.height){};

BinaryGrayImage::BinaryGrayImage(int width, int height) : height(height), width(width), th(128.0), matrix(IntMatrix(height, IntArray(width))){};

BinaryGrayImage::BinaryGrayImage(IntMatrix &tmatrix)
{
    matrix = tmatrix;
    width = tmatrix[0].size();
    height = tmatrix.size();
}

int BinaryGrayImage::operator()(int x_width, int y_height) const
{
    if (x_width < 0 || y_height < 0)
    {
        return false;
    }
    if (x_width >= width || y_height >= height)
    {
        return false;
    }

    return matrix[y_height][x_width];
}

int &BinaryGrayImage::operator()(int x_width, int y_height)
{
    if (x_width < 0 || y_height < 0)
    {
        std::cout << std::endl
                  << x_width << " " << y_height << std::endl;
        throw std::runtime_error("outofbounds");
    }
    if (x_width >= width || y_height >= height)
    {
        std::cout << std::endl
                  << x_width << " " << y_height << std::endl;
        throw std::runtime_error("outof bounds");
    }
    return matrix[y_height][x_width];
}