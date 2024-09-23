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
};