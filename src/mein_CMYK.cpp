#include "mein_CMYK.hpp"
#include "ImageProcessingFunctions.hpp"

std::tuple<double, double, double, double> CMYK_mein::_RGBtoCMYK_(double r, double g, double b)
{
    double c, m, y, k;
    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;
    double cmax = std::max(std::max(r, g), b);
    k = 1 - cmax;
    if (k == 1)
    {
        c = m = y = 0.0;
    }
    else
    {

        c = (1 - r - k) / (1 - k);
        m = (1 - g - k) / (1 - k);
        y = (1 - b - k) / (1 - k);
    }

    return std::make_tuple(c, m, y, k);
}

std::tuple<double, double, double> CMYK_mein::_CMYKtoRGB_(double c, double m, double y, double k)
{
    double r, g, b;
    r = 255 * (1 - c) * (1 - k);
    g = 255 * (1 - m) * (1 - k);
    b = 255 * (1 - y) * (1 - k);

    return std::make_tuple(r, g, b);
}

CMYK_mein::CMYK_mein(){};