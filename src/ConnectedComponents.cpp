#include "ConnectedComponents.hpp"

UnionFind::UnionFind(int n) : parent(n), rank(n, 0)
{
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
    }
}

int UnionFind::find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

void UnionFind::unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY)
    {
        if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
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
void moore_rasterscan(const BinaryGrayImage &img, std::vector<label_und_pixel> &labels, UnionFind &uf, int &label)
{
    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            if (!img(x, y))
                continue;

            pixelcoordinate pc = {x, y};
            std::vector<int> neighbors;

            // Check 8-connectivity neighbors
            if (checkboundary(x - 1, img.width))
                neighbors.push_back(checkinside({x - 1, y}, labels)); // Left
            if (checkboundary(y - 1, img.height))
                neighbors.push_back(checkinside({x, y - 1}, labels)); // Top
            if (checkboundary(x - 1, img.width) && checkboundary(y - 1, img.height))
                neighbors.push_back(checkinside({x - 1, y - 1}, labels)); // Top-left
            if (checkboundary(x + 1, img.width) && checkboundary(y - 1, img.height))
                neighbors.push_back(checkinside({x + 1, y - 1}, labels)); // Top-right
            if (checkboundary(x + 1, img.width))
                neighbors.push_back(checkinside({x + 1, y}, labels)); // Right
            if (checkboundary(y + 1, img.height))
                neighbors.push_back(checkinside({x, y + 1}, labels)); // Bottom
            if (checkboundary(x - 1, img.width) && checkboundary(y + 1, img.height))
                neighbors.push_back(checkinside({x - 1, y + 1}, labels)); // Bottom-left
            if (checkboundary(x + 1, img.width) && checkboundary(y + 1, img.height))
                neighbors.push_back(checkinside({x + 1, y + 1}, labels)); // Bottom-right

            // Filter out zeroes (background)
            neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), 0), neighbors.end());

            if (neighbors.empty())
            {
                labels.push_back({label, pc});
                label++;
            }
            else
            {
                int minLabel = *std::min_element(neighbors.begin(), neighbors.end());
                labels.push_back({minLabel, pc});

                // Unite all neighbor labels
                for (int neighborLabel : neighbors)
                {
                    uf.unite(minLabel, neighborLabel);
                }
            }
        }
    }
}