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