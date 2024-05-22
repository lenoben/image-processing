#ifndef SIMPLE_LIB_IMAGE_H
#define SIMPLE_LIB_IMAGE_H

#include <stdio.h>
#include <vector>
#include "../png/png.h"
#include <iostream>
#include <string>
#include <algorithm>

typedef unsigned char Byte;

struct RGBA
{
	RGBA() : r(0), g(0), b(0), a(255) {}
	RGBA(Byte r, Byte g, Byte b, Byte a = 255) : r(r), g(g), b(b), a(a) {}
	RGBA(Byte lum) : r(lum), g(lum), b(lum), a(255) {}

	Byte luminance() const
	{
		return 0.299 * r + 0.587 * g + 0.114 * b;
	}

	Byte r, g, b, a;
};

class GrayscaleImage;

class ColorImage
{
public:
	ColorImage();

	ColorImage(int width, int height);

	ColorImage(const GrayscaleImage &im);

	RGBA &operator()(int x, int y);

	RGBA operator()(int x, int y) const;

	RGBA Get(int x, int y) const;

	void Clear();

	int GetWidth() const;

	int GetHeight() const;

	void Save(std::string filename);

	void Load(std::string filename);

private:
	std::vector<RGBA> data;
	int width, height;
};

class GrayscaleImage
{
public:
	GrayscaleImage();

	GrayscaleImage(int width, int height);

	GrayscaleImage(const ColorImage &im);

	int GetWidth() const;

	int GetHeight() const;

	Byte &operator()(int x, int y);

	Byte operator()(int x, int y) const;

	Byte Get(int x, int y) const;

	void Save(std::string filename);

	void Load(std::string filename);

private:
	std::vector<Byte> data;
	int width, height;
};

#endif