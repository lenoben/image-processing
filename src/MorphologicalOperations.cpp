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