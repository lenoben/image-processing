#include "BinaryGray.hpp"

BinaryGrayImage::BinaryGrayImage(const BinaryGrayImage &other) : matrix(other.matrix), width(other.width), height(other.height), th(other.th){};

BinaryGrayImage::BinaryGrayImage(int width, int height) : height(height), width(width), th(128.0), matrix(IntMatrix(height, IntArray(width))){};

BinaryGrayImage::BinaryGrayImage(int width, int height, float tth) : height(height), width(width), th(tth), matrix(IntMatrix(height, IntArray(width))){};

BinaryGrayImage::BinaryGrayImage(IntMatrix &tmatrix)
{
    matrix = tmatrix;
    width = tmatrix[0].size();
    height = tmatrix.size();
}

void BinaryGrayImage::Load(GrayscaleImage &img, bool adaptativeThreshold, float manualThreshold)
{
    th = manualThreshold;
    float prevth = th;
    width = img.GetWidth();
    height = img.GetHeight();

    matrix = IntMatrix(height, IntArray(width));

    double sum_true, sum_false, count_true, count_false;

    if (adaptativeThreshold)
    {
        do
        {
            prevth = th;
            sum_true = 0;
            sum_false = 0;
            count_true = 0;
            count_false = 0;
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    if (img(x, y) > th)
                    {
                        sum_true += img(x, y);
                        count_true++;
                    }
                    else
                    {
                        sum_false += img(x, y);
                        count_false++;
                    }
                }
            }
            th = float(sum_true / count_true + sum_false / count_false) / 2;
        } while (th != prevth);
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            (*this)(x, y) = img(x, y) > th ? 1 : 0;
        }
    }
}

int BinaryGrayImage::operator()(int x_width, int y_height) const
{
    if (x_width < 0 || y_height < 0)
    {
        return false;
    }
    if (x_width >= width || y_height >= height)
    {
        return false;
    }

    return matrix[y_height][x_width];
}

int &BinaryGrayImage::operator()(int x_width, int y_height)
{
    if (x_width < 0 || y_height < 0)
    {
        std::cout << std::endl
                  << x_width << " " << y_height << std::endl;
        throw std::runtime_error("outofbounds");
    }
    if (x_width >= width || y_height >= height)
    {
        std::cout << std::endl
                  << x_width << " " << y_height << std::endl;
        throw std::runtime_error("outof bounds");
    }
    return matrix[y_height][x_width];
}

void BinaryGrayImage::inverse()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y) = !(*this)(x, y);
        }
    }
}

void BinaryGrayImage::exportimg(GrayscaleImage &img)
{
    img = GrayscaleImage(width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            img(x, y) = (*this)(x, y) ? 255 : 0;
        }
    }
}

IntMatrix BinaryGrayImage::getMatrix() const
{
    return matrix;
}

IntMatrix &BinaryGrayImage::getMatrix()
{
    return matrix;
}