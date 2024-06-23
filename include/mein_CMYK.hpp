#pragma once

#include "ImageHeader.hpp"

class CMYK_mein
{
    CmykMatrix matrix;

    std::tuple<double, double, double, double> _RGBtoCMYK_(double r, double g, double b);

    std::tuple<double, double, double> _CMYKtoRGB_(double c, double m, double y, double k);

public:
    int height;
    int width;

    CMYK_mein();

    CMYK_mein(int width, int height);

    CMYK_mein(ColorImage &img);

    CMYK_mein(const CMYK_mein &other);

    void toRGB(ColorImage &image);

    cmyk operator()(int x_width, int y_height) const;

    cmyk &operator()(int x_width, int y_height);

    void setC(float value);

    void setM(float value);

    void setY(float value);
};