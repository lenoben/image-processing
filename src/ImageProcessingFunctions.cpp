#include "ImageProcessingFunctions.hpp"

double slamp(double x)
{
    return std::clamp(x, 0.0, 255.0);
}

double _HStoR_(double h, double x, double y)
{
    if (0 <= h && h < 60)
    {
        return x;
    }
    else if (60 <= h && h < 120)
    {
        return y;
    }
    else if (120 <= h && h < 180)
    {
        return 0;
    }
    else if (180 <= h && h < 240)
    {
        return 0;
    }
    else if (240 <= h && h < 300)
    {
        return y;
    }
    else
    {
        return x;
    }
}

double _HStoG_(double h, double x, double y)
{
    if (0 <= h && h < 60)
    {
        return y;
    }
    else if (60 <= h && h < 120)
    {
        return x;
    }
    else if (120 <= h && h < 180)
    {
        return x;
    }
    else if (180 <= h && h < 240)
    {
        return y;
    }
    else if (240 <= h && h < 300)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

double _HStoB_(double h, double x, double y)
{
    if (0 <= h && h < 60)
    {
        return 0;
    }
    else if (60 <= h && h < 120)
    {
        return 0;
    }
    else if (120 <= h && h < 180)
    {
        return y;
    }
    else if (180 <= h && h < 240)
    {
        return x;
    }
    else if (240 <= h && h < 300)
    {
        return x;
    }
    else
    {
        return y;
    }
}