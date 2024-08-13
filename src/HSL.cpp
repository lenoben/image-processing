#include "HSL.hpp"
#include "ImageProcessingFunctions.hpp"

HSL::HSL(){};

std::tuple<double, double, double> HSL::_RGBtoHSL_(double r, double g, double b)
{

    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;
    double cmin = std::min(std::min(r, g), b);
    double cmax = std::max(std::max(r, g), b);
    double delta = cmax - cmin;

    double h, s, l;

    l = (cmin + cmax) / 2;

    if (delta == 0)
    {
        h = 0;
        s = 0;
    }
    else
    {
        s = delta / (1 - std::fabs(2 * l - 1));
        if (cmax == r)
        {
            double result = (g - b) / delta;
            h = 60 * (fmod(result, 6));
        }
        if (cmax == g)
        {
            double result = ((b - r) / delta) + 2;
            h = 60 * result;
        }
        if (cmax == b)
        {
            double result = ((r - g) / delta) + 4;
            h = 60 * result;
        }
    }

    return std::make_tuple(h, s, l);
}