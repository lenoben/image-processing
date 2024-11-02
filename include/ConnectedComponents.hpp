#pragma once
#include "BinaryGray.hpp"

class UnionFind
{
public:
    UnionFind(int n);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

bool checkboundary(int x, int xmax);

int checkinside(pixelcoordinate pc, std::vector<label_und_pixel> &lup);