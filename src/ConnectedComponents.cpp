#include "ConnectedComponents.hpp"

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