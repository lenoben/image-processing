#include "HSL.hpp"
#include "ImageProcessingFunctions.hpp"

HSL::HSL(){};

HSL::HSL(int width, int height) : width(width), height(height), matrix(HslMatrix(height, HslArray(width))){};

HSL::HSL(const HSL &other) : width(other.width), height(other.height), matrix(other.matrix){};

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

std::tuple<double, double, double> HSL::_HSLtoRGB_(double h, double s, double l)
{
    double r, g, b;
    double x = (1 - std::abs(2 * l - 1)) * s;
    double m = l - x / 2;
    double result = fmod(h / 60, 2);
    double y = x * (1 - std::abs(result - 1));
    r = m + _HStoR_(h, x, y);
    g = m + _HStoG_(h, x, y);
    b = m + _HStoB_(h, x, y);

    r = slamp(r * 255);
    g = slamp(g * 255);
    b = slamp(b * 255);

    return std::make_tuple(r, g, b);
}

hsl HSL::operator()(int x_width, int y_height) const
{
    return matrix[y_height][x_width];
}

hsl &HSL::operator()(int x_width, int y_height)
{
    return matrix[y_height][x_width];
}

void HSL::rotateH(float angle)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).h = fmod((*this)(x, y).h + angle, 360.0);
        }
    }
}

void HSL::rotateS(float angle)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).s = fmod((*this)(x, y).s + angle, 360.0);
        }
    }
}

void HSL::rotateL(float angle)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).l = fmod((*this)(x, y).l + angle, 360.0);
        }
    }
}