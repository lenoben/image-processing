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