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

    hsv operator()(int x_width, int y_height) const;

    hsv &operator()(int x_width, int y_height);
};