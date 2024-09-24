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
