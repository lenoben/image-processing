#include "HSI.hpp"
#include "ImageProcessingFunctions.hpp"

std::tuple<double, double, double> HSI::_RGBtoHSI_(double R, double G, double B)
{

    double h, s, i;
    R = R / 255.0;
    G = G / 255.0;
    B = B / 255.0;

    double minVal = std::min(std::min(R, G), B);
    double maxVal = std::max(std::max(R, G), B);

    double delta = maxVal - minVal;

    i = (R + G + B) / 3.0f;

    if (delta == 0)
    {
        s = 0;
        h = 0; // Undefined
    }
    else
    {
        s = 1 - minVal / i;

        double denom = sqrt((R - G) * (R - G) + (R - B) * (G - B));
        double theta = acos(0.5 * ((R - G) + (R - B)) / denom);

        if (B <= G)
        {
            h = theta;
        }
        else
        {
            h = 2 * M_PI - theta;
        }
    }

    // Convert radians to degrees
    h *= 180 / M_PI;

    return std::make_tuple(h, s, i);
}

std::tuple<double, double, double> HSI::_HSItoRGB_(double h, double s, double i)
{
    double r, g, b;
    if (s == 0)
    {
        r = g = b = i;
    }
    else
    {
        float hh = h * M_PI / 180; // Convert degrees to radians

        if (hh < 2 * M_PI / 3)
        {
            r = i * (1 + s * cos(hh) / cos(M_PI / 3 - hh));
            b = i * (1 - s);
            g = 3 * i - (r + b);
        }
        else if (hh < 4 * M_PI / 3)
        {
            hh -= 2 * M_PI / 3;
            g = i * (1 + s * cos(hh) / cos(M_PI / 3 - hh));
            r = i * (1 - s);
            b = 3 * i - (g + r);
        }
        else
        {
            hh -= 4 * M_PI / 3;
            b = i * (1 + s * cos(hh) / cos(M_PI / 3 - hh));
            g = i * (1 - s);
            r = 3 * i - (b + g);
        }
    }

    r = slamp(r * 255);
    g = slamp(g * 255);
    b = slamp(b * 255);

    return std::make_tuple(r, g, b);
}

HSI::HSI() {};

HSI::HSI(int width, int height) : width(width), height(height), matrix(HsiMatrix(height, HsiArray(width))) {};

HSI::HSI(const HSI &other) : width(other.width), height(other.height), matrix(other.matrix) {};

HSI::HSI(ColorImage &img) : width(img.GetWidth()), height(img.GetHeight())
{
    matrix = HsiMatrix(height, HsiArray(width));
    for (int x = 0; x < img.GetWidth(); x++)
    {
        for (int y = 0; y < img.GetHeight(); y++)
        {
            std::tie((*this)(x, y).h, (*this)(x, y).s, (*this)(x, y).i) = _RGBtoHSI_(img(x, y).r, img(x, y).g, img(x, y).b);
        }
    }
};

void HSI::toRGB(ColorImage &image)
{
    ColorImage img(width, height);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::tie(img(x, y).r, img(x, y).g, img(x, y).b) = _HSItoRGB_((*this)(x, y).h, (*this)(x, y).s, (*this)(x, y).i);
        }
    }

    image = img;
}

hsi HSI::operator()(int x_width, int y_height) const
{
    return matrix[y_height][x_width];
}

hsi &HSI::operator()(int x_width, int y_height)
{
    return matrix[y_height][x_width];
}

void HSI::rotateH(float angle)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).h = fmod((*this)(x, y).h + angle, 360.0);
        }
    }
}

void HSI::rotateS(float angle)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).s = fmod((*this)(x, y).s + angle, 360.0);
        }
    }
}

void HSI::rotateI(float angle)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y).i = fmod((*this)(x, y).i + angle, 360.0);
        }
    }
}

void HSI::applyThreshold(BinaryGrayImage &img, double hmax, double hmin, double smax, double smin, double imax, double imin)
{
    BinaryGrayImage out(width, height);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if ((*this)(x, y).h >= hmin && (*this)(x, y).s >= smin && (*this)(x, y).i >= imin && (*this)(x, y).h <= hmax && (*this)(x, y).s <= smax && (*this)(x, y).i <= imax)
            {
                out(x, y) = 1;
            }
            else
            {
                out(x, y) = 0;
            }
        }
    }
    img = out;
}