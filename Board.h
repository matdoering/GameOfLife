#pragma once

#include <unordered_map>
#include "Cell.h"
#include <bits/stdc++.h>
#include <utility>

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Board {
public:
    Board();
    void updateNeighbors(int x, int y, bool state);

    void setDrawingRegion(std::pair<int,int> xDim, std::pair<int, int> yDim); /// region for drawing the game of life board
    bool setCellState(int x, int y, bool state, bool doNotUpdateNeighbors = false); /// Updates the cell's state. Returns true if the state has changed.
    bool getCellState(int x, int y);
    Cell& getCell(int x, int y);
    int getCellLivingNeighborCount(int x, int y);
    int initialize(double rateOfLivingCells, std::pair<int,int> xDim, std::pair<int,int> yDim);
    void update(); // next cycle of replication
    std::string toString(); /// show board on console
    const std::pair<int,int>& getXDim();
    const std::pair<int,int>& getYDim();

private:
    std::unordered_map<std::pair<int, int>, Cell, hash_pair> m_cells;
    std::pair<int,int> m_xDim = std::make_pair(-25,25); /// for drawing only
    std::pair<int,int> m_yDim = std::make_pair(-25,25); /// for drawing only

};
