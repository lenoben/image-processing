#include "MorphologicalOperations.hpp"

void printMatrix(IntMatrix &Tmatrix)
{
    for (const auto &row : Tmatrix)
    {
        for (const auto &elem : row)
        {
            // std::cout << (elem ? "X" : " ") << " ";
            std::cout << (elem ? "[X]" : "[ ]") << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

IntMatrix flipXY(IntMatrix Tmatrix)
{
    auto Nmatrix = Tmatrix;
    int nx = 0;
    int ny = 0;
    for (int x = Tmatrix[0].size() - 1; x >= 0; x--)
    {
        for (int y = Tmatrix.size() - 1; y >= 0; y--)
        {
            Nmatrix[ny][nx] = Tmatrix[y][x];
            ny++;
        }
        ny = 0;
        nx++;
    }

    return Nmatrix;
}

BinaryGrayImage Dilation(const BinaryGrayImage &img, IntMatrix kernel)
{
    int radius = (kernel.size() - 1) / 2;
    if (radius == 0)
    {
        throw std::runtime_error("dilation kernel is 2x2");
    }

    BinaryGrayImage dilate(img.width + (radius * 2), img.height + (radius * 2));
    dilate.setAll(false);
    BinaryGrayImage copy = img;
    copy.enlarge(dilate.width, dilate.height);
    BinaryGrayImage dcopy = copy;
    dcopy.enlarge(dilate.width + (radius * 2), dilate.height + (radius * 2));

    int my = 0;
    for (int y = 0; y < img.height + (radius * 2); y++)
    {
        int mx = 0;
        for (int x = 0; x < img.width + (radius * 2); x++)
        {
            int copyx = x + radius;
            int copyy = y + radius;

            /**/
            bool logic = false;
            int yy = -radius;
            for (int yk = 0; yk < kernel.size(); yk++)
            {
                int xx = -radius;
                for (int xk = 0; xk < kernel[0].size(); xk++)
                {
                    logic |= kernel[yk][xk] & dcopy(copyx + xx, copyy + yy);
                    xx++;
                }
                yy++;
            }
            dilate(mx, my) = logic;
            mx++;
        }
        my++;
    }
    return dilate;
}

bool erods(bool kernel, bool img)
{
    if (kernel)
    {
        return img;
    }
    return false;
}

BinaryGrayImage Erosion(const BinaryGrayImage &img, IntMatrix kernel)
{
    int radius = (kernel.size() - 1) / 2;
    if (radius == 0)
    {
        throw std::runtime_error("dilation kernel is 2x2");
    }

    int truenum = 0;
    for (const auto &row : kernel)
    {
        for (const auto &cell : row)
        {
            truenum += cell;
        }
    }

    BinaryGrayImage erode(img.width, img.height);
    erode.setAll(0);
    BinaryGrayImage dcopy = img;
    dcopy.enlarge(img.width + (radius * 2), img.height + (radius * 2));

    int my = 0;
    for (int y = 0; y < dcopy.height - (radius * 2); y++)
    {
        int mx = 0;
        for (int x = 0; x < dcopy.width - (radius * 2); x++)
        {
            int copyx = x + radius;
            int copyy = y + radius;

            int logic = 0;
            int yy = -radius;
            for (int yk = 0; yk < kernel.size(); yk++)
            {
                int xx = -radius;
                for (int xk = 0; xk < kernel[0].size(); xk++)
                {
                    logic += erods(kernel[yk][xk], dcopy(copyx + xx, copyy + yy));
                    xx++;
                }
                yy++;
            }
            erode(mx, my) = (logic == truenum) ? 1 : 0;
            mx++;
        }
        // std::cout << std::endl;
        my++;
    }
    return erode;
}

// closing dilation + erosion
// opening erosion + dilation