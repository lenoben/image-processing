#include "Image.h"
#include "HSV.hpp"

int main()
{
    /*
    H => 68.00 on some websites its deg
    S => 73.00 on some websites its percentage
    V => 0.77 on some websites its percentage
    */
    std::cout << "HSV" << std::endl;
    ColorImage cimg;
    cimg.Load("lena.png");
    HSV
        hsv_h(cimg),
        hsv_s(cimg),
        hsv_v(cimg);

    hsv_h.rotateH(72.0);
    hsv_s.rotateS(72.0);
    hsv_v.rotateV(72.0);

    hsv_h.toRGB(cimg);
    cimg.Save("h_rotated.png");
    hsv_s.toRGB(cimg);
    cimg.Save("s_rotated.png");
    hsv_v.toRGB(cimg);
    cimg.Save("v_rotated.png");

    hsv_h.rotateS(72.0);
    hsv_h.toRGB(cimg);
    cimg.Save("hs_rotated.png");

    BinaryGrayImage bhsv;
    hsv_h.applyThreshold(bhsv, 144.0, 84.0, 99.0, 70.0, 1, 0);
    GrayscaleImage ghsv;
    bhsv.exportimg(ghsv);
    ghsv.Save("hsv_apply.png");

    std::cout << "H: " << hsv_h(int(hsv_h.width / 2), int(hsv_h.height / 2)).h << " S: " << hsv_h(int(hsv_h.width / 2), int(hsv_h.height / 2)).s << " V: " << hsv_h(int(hsv_h.width / 2), int(hsv_h.height / 2)).v << std::endl;
    return 0;
}