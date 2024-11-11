#include "BinaryGray.hpp"

BinaryGrayImage::BinaryGrayImage(const BinaryGrayImage &other) : matrix(other.matrix), width(other.width), height(other.height), th(other.th) {};

BinaryGrayImage::BinaryGrayImage(int width, int height) : height(height), width(width), th(128.0), matrix(IntMatrix(height, IntArray(width))) {};

BinaryGrayImage::BinaryGrayImage(int width, int height, float tth) : height(height), width(width), th(tth), matrix(IntMatrix(height, IntArray(width))) {};

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

void BinaryGrayImage::exportimg(ColorImage &img)
{
    img = ColorImage(width, height);

    for (int y = 0; y < height; y++)
    {
        RGBA nil{0, 0, 0, 255};
        for (int x = 0; x < width; x++)
        {
            img(x, y) = (*this)(x, y) ? img(x, y) : nil;
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

void BinaryGrayImage::operator|(const BinaryGrayImage &other)
{
    /*OR
    1 1 = 1
    1 0 = 1
    0 1 = 1
    0 0 = 0
    */
    if (width != other.width || height != other.height)
    {
        throw std::runtime_error("operator | dimension not equal");
        return;
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y) = (*this)(x, y) | other(x, y);
        }
    }
}

void BinaryGrayImage::operator&(const BinaryGrayImage &other)
{
    /*AND
    1 1 = 1
    1 0 = 0
    0 1 = 0
    0 0 = 0
    */
    if (width != other.width || height != other.height)
    {
        throw std::runtime_error("operator & dimension not equal");
        return;
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y) = (*this)(x, y) & other(x, y);
        }
    }
}

void BinaryGrayImage::operator^(const BinaryGrayImage &other)
{
    /*XOR
    1 1 = 0
    1 0 = 1
    0 1 = 1
    0 0 = 0
    */
    if (width != other.width || height != other.height)
    {
        throw std::runtime_error("operator xor dimension not equal");
        return;
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y) = (*this)(x, y) ^ other(x, y);
        }
    }
}

bool customlogic(bool x, bool y)
{
    if (x)
    {
        if (y)
            return false;
        return true;
        // 1 0 = 1
        // 1 1 = 0
    }
    return false;
}

BinaryGrayImage BinaryGrayImage::operator-(const BinaryGrayImage &other)
{
    BinaryGrayImage send(this->width, other.height, this->th);
    /*
    1 1 = 0
    0 1 = 0
    1 0 = 1
    0 0 = 0
    */
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            send(x, y) = customlogic((*this)(x, y), other(x, y));
        }
    }
    return send;
}

void BinaryGrayImage::printMatrix()
{
    if (this->height < 1 || this->width < 1)
        std::cout << "Cant print matrix a dimension is less than 1" << std::endl;

    for (const auto &row : this->matrix)
    {
        for (const auto &elem : row)
        {
            std::cout << (elem ? "[X]" : "[ ]") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void BinaryGrayImage::clear()
{
    width = 0;
    height = 0;
    th = 0.0;
    matrix = IntMatrix();
}

void BinaryGrayImage::setAll(bool boolean)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            (*this)(x, y) = boolean;
        }
    }
}

void BinaryGrayImage::enlarge(int nwidth, int nheight)
{
    if (!(nwidth > width && nheight > height))
    {
        // TODO: implement error handling
        return;
    }

    BinaryGrayImage ngray(nwidth, nheight);
    ngray.setAll(false);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            ngray(
                (x + (int)(nwidth - width) / 2),
                (y + (int)(nheight - height) / 2)) = (*this)(x, y);
        }
    }

    matrix = ngray.getMatrix();
    width = nwidth;
    height = nheight;
}

void BinaryGrayImage::shrink(IntMatrix &kernel)
{

    int radius = (kernel.size() - 1) / 2;
    BinaryGrayImage nshrink(width - (radius * 2), height - (radius));

    int ny = 0;
    int nx = 0;
    for (int x = radius; x < width - radius; x++)
    {
        for (int y = radius; y < height - radius; y++)
        {
            nshrink(nx, ny) = (*this)(x, y);
            ny++;
        }
        ny = 0;
        nx++;
    }

    matrix = nshrink.getMatrix();
    width = width - radius * 2;
    height = height - radius * 2;
}