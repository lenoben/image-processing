#ifndef _LIB_BINARY_GRAY
#define _LIB_BINARY_GRAY

#include "ImageHeader.hpp"

bool customlogic(bool x, bool y);

class BinaryGrayImage
{
    IntMatrix matrix;

public:
    int width;
    int height;
    float th; // threshold

public:
    /**
     * @brief Construct a new Binary Gray Image object
     *
     */
    BinaryGrayImage() {};

    /**
     * @brief Copy Constructor a new Binary Gray Image object
     *
     * @param other
     */
    BinaryGrayImage(const BinaryGrayImage &other);

    /**
     * @brief Construct a new Binary Gray Image object
     * with specified dimensions and a threshold of 128.0
     *
     * @param width
     * @param height
     */
    BinaryGrayImage(int width, int height);

    /**
     * @brief Construct a new Binary Gray Image object
     *
     * @param width
     * @param height
     * @param tth threshold for binary imagry
     */
    BinaryGrayImage(int width, int height, float tth);

    /**
     * @brief Construct a new Binary Gray Image object
     * with a specified matrix
     *
     * @usage: mostly used for demonstration purposes
     *
     * @param tmatrix
     */
    BinaryGrayImage(IntMatrix &tmatrix);

    /**
     * @brief Loads the binaryImage with data from a Grayscale Image
     * İt automatically converts it into binary image
     *
     * @param img
     * @param adaptativeThreshold
     * @param manualThreshold
     */
    void Load(GrayscaleImage &img, bool adaptativeThreshold = true, float manualThreshold = 128);

    int operator()(int x_width, int y_height) const;

    int &operator()(int x_width, int y_height);

    void inverse();

    /**
     * @brief converts the binaryİmage into a GrayscaleImage
     * overrides the GrayscaleImage class
     * @param img
     */
    void exportimg(GrayscaleImage &img);

    void exportimg(ColorImage &img);

    IntMatrix getMatrix() const;

    IntMatrix &getMatrix();

    void operator|(const BinaryGrayImage &other);

    void operator&(const BinaryGrayImage &other);

    void operator^(const BinaryGrayImage &other);

    BinaryGrayImage operator-(const BinaryGrayImage &other);

    void printMatrix();

    /**
     * @brief clears everything in the class even threshold is set to 0
     *
     */
    void clear();

    /**
     * @brief Set the All object to the boolean or int value set for it
     *
     * @param boolean
     */
    void setAll(bool boolean);
};

#endif