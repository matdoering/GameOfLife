#pragma once

#include <string>

std::string getStateRep(int x, int y, bool state, bool debug = false);

class Cell {
public:
    Cell(int x, int y, bool state);
    Cell();
    void setState(bool state);
    bool getState();
    int getX() const;
    int getY() const;
    int getLivingNeighborCount() const;
    void updateNeighborCount(bool newStateOfNeighbor);

private:
    bool m_state; // true: alive, false: dead
    int m_x, m_y;
    int m_livingNeighborCount = 0;
};
