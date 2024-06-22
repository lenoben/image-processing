#pragma once
#include "ImageHeader.hpp"
#include "BinaryGray.hpp"

class HSV
{
    HsvMatrix matrix;

    std::tuple<double, double, double> _RGBtoHSV_(double r, double g, double b);

    std::tuple<double, double, double> _HSVtoRGB_(double h, double s, double v);

public:
    int width;
    int height;

    HSV();

    HSV(int width, int height);

    HSV(const HSV &other);

    HSV(ColorImage &img);

    void toRGB(ColorImage &image);

    hsv operator()(int x_width, int y_height) const;

    hsv &operator()(int x_width, int y_height);
    
    void rotateH(float angle);

    void rotateS(float angle);

    void rotateV(float angle);

    void applyThreshold(BinaryGrayImage &img, double hmax, double hmin, double smax, double smin, double vmax, double vim);
};