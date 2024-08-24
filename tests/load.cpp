#include "Image.h"
#include <cassert>

int main()
{
    GrayscaleImage gimg;
    ColorImage cimg;

    gimg.Load("lena.png");
    cimg.Load("lena.png");
    assert(gimg.GetHeight() > 0);
    assert(cimg.GetWidth() > 0);

    return 0;
}