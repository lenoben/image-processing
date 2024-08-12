#pragma once
#include "ImageHeader.hpp"

class HSL
{
    HslMatrix matrix;

    std::tuple<double, double, double> _RGBtoHSL_(double r, double g, double b);

    std::tuple<double, double, double> _HSLtoRGB_(double h, double s, double l);

public:
    int width;
    int height;

    HSL();

    HSL(int width, int height);

    HSL(const HSL &other);
};