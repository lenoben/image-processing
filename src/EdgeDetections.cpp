#include "EdgeDetections.hpp"

GrayscaleImage meanBlur(const GrayscaleImage &img)
{
    GrayscaleImage out(img.GetWidth(), img.GetHeight());
    IntMatrix kernel(3, IntArray(3));
    for (auto &row : kernel)
        std::fill(row.begin(), row.end(), 1);

    for (int x = 0; x < img.GetWidth(); x++)
    {
        out(x, 0) = img(x, 0);
        out(x, img.GetHeight() - 1) = img(x, img.GetHeight() - 1);
    }
    for (int y = 0; y < img.GetHeight(); y++)
    {
        out(0, y) = img(0, y);
        out(img.GetWidth() - 1, y) = img(img.GetWidth() - 1, y);
    }
    for (int x = 1; x < img.GetWidth() - 1; x++)
    {
        for (int y = 1; y < img.GetHeight() - 1; y++)
        {
            double sum = 0.0;
            for (int xk = 0; xk < kernel.size(); xk++)
            {
                for (int yk = 0; yk < kernel.size(); yk++)
                {
                    sum += kernel[xk][yk] * img(x - 1 + xk, y - 1 + yk);
                }
            }
            out(x, y) = sum / 9.0; // Normalizing by dividing by the sum of the kernel values
        }
    }

    return out;
}
