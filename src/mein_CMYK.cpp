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

CMYK_mein::CMYK_mein(int width, int height) : height(height), width(width), matrix(CmykMatrix(height, CmykArray(width))){};

CMYK_mein::CMYK_mein(ColorImage &img) : width(img.GetWidth()), height(img.GetHeight())
{
    matrix = CmykMatrix(height, CmykArray(width));
    for (int x = 0; x < img.GetWidth(); x++)
    {
        for (int y = 0; y < img.GetHeight(); y++)
        {
            std::tie((*this)(x, y).c, (*this)(x, y).m, (*this)(x, y).y, (*this)(x, y).k) = _RGBtoCMYK_(img(x, y).r, img(x, y).g, img(x, y).b);
        }
    }
};

CMYK_mein::CMYK_mein(const CMYK_mein &other) : matrix(other.matrix), height(other.height), width(other.width){};

void CMYK_mein::toRGB(ColorImage &image)
{
    ColorImage img(width, height);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::tie(img(x, y).r, img(x, y).g, img(x, y).b) = _CMYKtoRGB_((*this)(x, y).c, (*this)(x, y).m, (*this)(x, y).y, (*this)(x, y).k);
        }
    }

    image = img;
}

cmyk CMYK_mein::operator()(int x_width, int y_height) const
{
    return matrix[y_height][x_width];
}

cmyk &CMYK_mein::operator()(int x_width, int y_height)
{
    return matrix[y_height][x_width];
}

void CMYK_mein::setC(float value)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).c = value;
        }
    }
}

void CMYK_mein::setM(float value)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).m = value;
        }
    }
}

void CMYK_mein::setY(float value)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).y = value;
        }
    }
}