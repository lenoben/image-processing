#include "Image.h"
#include "BinaryGray.hpp"
#include <cassert>

int main()
{
    GrayscaleImage gimg;
    ColorImage cimg;

    gimg.Load("lena.png");
    BinaryGrayImage bimg;
    bimg.Load(gimg);
    assert(bimg.height == gimg.GetHeight());
    assert(bimg.width == gimg.GetWidth());

    bimg.exportimg(gimg);
    gimg.Save("adaptative_lena.png");

    return 0;
}