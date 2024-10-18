#pragma once
#include "ImageHeader.hpp"
#include "BinaryGray.hpp"

class HSI
{
    HsiMatrix matrix;

    std::tuple<double, double, double> _RGBtoHSI_(double R, double G, double B);

    std::tuple<double, double, double> _HSItoRGB_(double h, double s, double i);

public:
    int width;
    int height;

    HSI();

    HSI(int width, int height);

    HSI(const HSI &other);

    HSI(ColorImage &img);

    void toRGB(ColorImage &image);

    hsi operator()(int x_width, int y_height) const;

    hsi &operator()(int x_width, int y_height);

    void rotateH(float angle);

    void rotateS(float angle);

    void rotateI(float angle);

    void applyThreshold(BinaryGrayImage &img, double hmax, double hmin, double smax, double smin, double imax, double imin);
};