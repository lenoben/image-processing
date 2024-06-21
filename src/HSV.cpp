#include "HSV.hpp"
#include "ImageProcessingFunctions.hpp"

std::tuple<double, double, double> HSV::_RGBtoHSV_(double r, double g, double b)
{

    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;
    double cmin = std::min({r, g, b});
    double cmax = std::max({r, g, b});
    double delta = cmax - cmin;
    double h, s, v = cmax;

    if (delta == 0)
    {
        h = 0;
    }
    else
    {
        if (cmax == r)
        {
            h = 60 * (fmod(((g - b) / delta), 6));
        }
        else if (cmax == g)
        {
            h = 60 * (((b - r) / delta) + 2);
        }
        else if (cmax == b)
        {
            h = 60 * (((r - g) / delta) + 4);
        }
    }

    if (h < 0)
        h += 360;

    s = (cmax == 0) ? 0 : delta / cmax;

    return std::make_tuple(h, s, v);
}

std::tuple<double, double, double> HSV::_HSVtoRGB_(double h, double s, double v)
{
    double c = v * s;
    double x = c * (1 - std::abs(fmod(h / 60.0, 2) - 1));
    double m = v - c;

    double r, g, b;
    if (0 <= h && h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (60 <= h && h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (120 <= h && h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (180 <= h && h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (240 <= h && h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    r = slamp((r + m) * 255);
    g = slamp((g + m) * 255);
    b = slamp((b + m) * 255);

    return std::make_tuple(r, g, b);
}

HSV::HSV(){};

HSV::HSV(int width, int height) : width(width), height(height), matrix(HsvMatrix(height, HsvArray(width))){};

hsv HSV::operator()(int x_width, int y_height) const
{
    return matrix[y_height][x_width];
}

hsv &HSV::operator()(int x_width, int y_height)
{
    return matrix[y_height][x_width];
}