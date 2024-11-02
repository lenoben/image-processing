#include "ConnectedComponents.hpp"

UnionFind::UnionFind(int n) : parent(n), rank(n, 0)
{
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
    }
}

bool checkboundary(int x, int xmax)
{
    return x >= 0 && x < xmax;
}

int checkinside(pixelcoordinate pc, std::vector<label_und_pixel> &lup)
{
    for (const auto &item : lup)
    {
        if (item.second == pc)
        {
            return item.first;
        }
    }
    return 0;
}