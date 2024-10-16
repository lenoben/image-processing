#pragma once
#include "ImageHeader.hpp"
#include "BinaryGray.hpp"

class HSV
{
    HsvMatrix matrix;

    std::tuple<double, double, double> _RGBtoHSV_(double r, double g, double b);

    std::tuple<double, double, double> _HSVtoRGB_(double h, double s, double v);

public:
    int width;
    int height;

    /**
     * @brief Construct a new HSV object
     *  makes a hsv class with 0 width and 0 height and empty matrix
     */
    HSV();

    /**
     * @brief Construct a new HSV object with the matrix having those dimensions
     *
     * @param width
     * @param height
     */
    HSV(int width, int height);

    /**
     * @brief Construct a new HSV object with the width and height from another hsv
     * copys the matrix information too
     *
     * @param other
     */
    HSV(const HSV &other);

    /**
     * @brief applies the HSV transformation to the colorimg class
     * and saves it in its matrix
     *
     * @param img
     */
    HSV(ColorImage &img);

    /**
     * @brief converts the hsv information it has in its matrix into the colorimg
     *
     * @param image
     */
    void toRGB(ColorImage &image);

    hsv operator()(int x_width, int y_height) const;

    hsv &operator()(int x_width, int y_height);

    /**
     * @brief rotates the H in HSV
     *
     * @param angle
     */
    void rotateH(float angle);

    /**
     * @brief rotates the S in HSV
     *
     * @param angle
     */
    void rotateS(float angle);

    /**
     * @brief rotates the V in HSV
     *
     * @param angle
     */
    void rotateV(float angle);

    /**
     * @brief Used to make a specific selection of HSV values from the hsv information stored
     * in the matrix. overrides the binaryimage class
     *
     * @usages: can be used to filter colors from an  image
     *
     * @param img binaryGrayImage that will be populated
     * @param hmax maxmium hue
     * @param hmin minimum hue
     * @param smax maxmium saturation
     * @param smin minimum saturation
     * @param vmax v max
     * @param vim  v min
     *
     * @error: this.matrix must not be empty
     */
    void applyThreshold(BinaryGrayImage &img, double hmax, double hmin, double smax, double smin, double vmax, double vim);
};