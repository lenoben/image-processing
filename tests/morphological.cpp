#include "Image.h"
#include "MorphologicalOperations.hpp"

int main()
{
    std::cout << "***---Morphology---***" << std::endl;
    IntMatrix exampleimage = {
        {0, 1, 1, 1, 0, 0},
        {
            1,
            1,
            0,
            1,
            0,
            1,
        },
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1},
        {1, 0, 0, 1, 1, 1}};

    BinaryGrayImage eimg(exampleimage);

    IntMatrix kernel = {
        {0, 0, 0},
        {0, 1, 1},
        {0, 0, 0}};
    // IntMatrix kernel = {
    //     {0, 0, 1, 0, 0},
    //     {0, 1, 1, 1, 0},
    //     {1, 1, 0, 1, 1},
    //     {0, 1, 1, 1, 0},
    //     {0, 0, 1, 0, 0}};
    kernel = flipXY(kernel); // rectangele/circle filters for shape

    std::cout << "Example image matrix" << std::endl;
    printMatrix(eimg.getMatrix());

    std::cout << "Example Kernel" << std::endl;
    printMatrix(kernel);
    BinaryGrayImage dilated = Dilation(eimg, kernel);
    std::cout << "Dilated image matrix" << std::endl;
    printMatrix(dilated.getMatrix());

    std::cout << "Eroded image matrix" << std::endl;
    BinaryGrayImage eroded = Erosion(eimg, kernel);
    printMatrix(eroded.getMatrix());

    std::cout << "Closed image matrix => dilation + erosion" << std::endl;
    BinaryGrayImage closed = Erosion(dilated, kernel);
    closed.shrink(kernel);
    closed.printMatrix();

    std::cout << "Opened image matrix => erosion + dilation" << std::endl;
    BinaryGrayImage opened = Dilation(eroded, kernel);
    opened.shrink(kernel);
    opened.printMatrix();
    return 0;
}