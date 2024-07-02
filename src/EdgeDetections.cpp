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

Matrix getGaussianKernel(int size, double sigma)
{
    Matrix kernel(size, Array(size)); // 5x5
    double sum = 0.0;
    // due to gaussian kernel been symmetrical
    int radius = (size - 1) / 2;

    /*
    Gaussian formula = 1/(2* pi * sigma* sigma) * exp (- (x *x + y *y)/(2 * sigma * sigma))
    */
    double constant1 = 1 / (2 * M_PI * sigma * sigma);
    double constant2 = 2 * sigma * sigma;

    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            kernel[x + radius][y + radius] = constant1 * exp(-(x * x + y * y) / constant2);
            sum += kernel[x + radius][y + radius];
        }
    }

    // normalize kernel
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            kernel[i][j] /= sum;
        }
    }
    return kernel;
}

void applyKernel(const GrayscaleImage &image, Matrix &mkernel, GrayscaleImage &output)
{
    int radius = (mkernel.size() - 1) / 2;

    for (int x = 0; x < image.GetWidth(); x++)
    {
        for (int y = 0; y < radius; y++)
        {

            output(x, y) = image(x, y);
        }
        output(x, image.GetHeight() - 1) = image(x, image.GetHeight() - 1);
    }
    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < radius; x++)
        {

            output(x, y) = image(x, y);
        }
        output(image.GetWidth() - 1, y) = image(image.GetWidth() - 1, y);
    }

    for (int x = 0 + radius; x < image.GetWidth() - radius; x++)
    {
        for (int y = 0 + radius; y < image.GetHeight() - radius; y++)
        {

            // kernel
            for (int xk = 0; xk < mkernel.size(); xk++)
            {
                for (int yk = 0; yk < mkernel.size(); yk++)
                {
                    output(x, y) += mkernel[xk][yk] * image(x - radius + xk, y - radius + yk);
                }
            }
        }
    }
}

GrayscaleImage applyGaussian(const GrayscaleImage &image, int size, double sigma)
{
    GrayscaleImage output(image.GetWidth(), image.GetHeight());
    Matrix mkernel = getGaussianKernel(size, sigma);
    applyKernel(image, mkernel, output);

    return output;
}

GrayscaleImage robertsCross(const GrayscaleImage &image)
{
    int width = image.GetWidth();
    int height = image.GetHeight();
    GrayscaleImage result(width, height);

    // Iterate over each pixel in the image (excluding the border pixels)
    for (int y = 0; y < height - 1; ++y)
    {
        for (int x = 0; x < width - 1; ++x)
        {
            // Apply the Robert's Cross kernel
            int gx = image(x, y) - image(x + 1, y + 1);
            int gy = image(x + 1, y) - image(x, y + 1);
            // Calculate the gradient magnitude
            int gradientMagnitude = std::abs(gx) + std::abs(gy);
            // Set the resulting pixel value
            result(x, y) = std::clamp(gradientMagnitude, 0, 255);
        }
    }
    return result;
}

Gradient prewitt(const GrayscaleImage &img)
{
    const int horizontalPrewittKernel[3][3] = {
        {-1, 0, 1},
        {-1, 0, 1},
        {-1, 0, 1}};

    const int verticalPrewittKernel[3][3] = {
        {-1, -1, -1},
        {0, 0, 0},
        {1, 1, 1}};
    int width = img.GetWidth();
    int height = img.GetHeight();
    GrayscaleImage result(width, height);
    GrayscaleImage direction(width, height);

    // Iterate over each pixel in the image (excluding the border pixels)
    for (int x = 1; x < width - 1; ++x)
    {
        for (int y = 1; y < height - 1; ++y)
        {
            // Apply the horizontal Prewitt kernel
            double sumX = 0.0;
            for (int xk = 0; xk < 3; ++xk)
            {
                for (int yk = 0; yk < 3; ++yk)
                {
                    sumX += horizontalPrewittKernel[xk][yk] * img(x - 1 + xk, y - 1 + yk);
                }
            }

            // Apply the vertical Prewitt kernel
            double sumY = 0.0;
            for (int xk = 0; xk < 3; ++xk)
            {
                for (int yk = 0; yk < 3; ++yk)
                {
                    sumY += verticalPrewittKernel[xk][yk] * img(x - 1 + xk, y - 1 + yk);
                }
            }

            // Compute the magnitude of the gradient
            int magnitude = std::clamp(static_cast<int>(std::sqrt(sumX * sumX + sumY * sumY)), 0, 255);
            // compute direction in degress 0-360
            float angle = std::atan2(sumY, sumX) * 180 / M_PI;
            if (angle < 0)
                angle += 360;
            direction(x, y) = static_cast<int>(angle);

            // Set the resulting pixel value
            result(x, y) = magnitude;
        }
    }

    return {result, direction};
}