
#include "Cell.h"

std::string getStateRep(int x, int y, bool state, bool debug) {
    std::string stateRep = state ? "1" : "0";
    if (debug) {
        stateRep += "[" + std::to_string(x) + "," + std::to_string(y) + "]";
    }
    return stateRep;
}

Cell::Cell(int x, int y, bool state) : m_x(x), m_y(y), m_state(state) {
}

Cell::Cell() : m_x(0), m_y(0), m_state(false) {
}
void Cell::setState(bool state) {
    m_state = state;
}
bool Cell::getState() {
    return m_state;
}

int Cell::getX() const {
    return m_x;
}
int Cell::getY() const {
    return m_y;
}

int Cell::getLivingNeighborCount() const {
    return m_livingNeighborCount;
}

void Cell::updateNeighborCount(bool newStateOfNeighbor) {
    if (newStateOfNeighbor) { // neighbor has become alive
        m_livingNeighborCount++;
    } else {
        // neighbor cell has died
        m_livingNeighborCount--;
    }
}


