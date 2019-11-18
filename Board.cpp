
#include "Board.h"
#include <cstdlib>
#include "Cell.h"
#include <utility>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iostream>

Board::Board() {}

void Board::setDrawingRegion(std::pair<int,int> xDim, std::pair<int, int> yDim) {
    m_xDim = xDim;
    m_yDim = yDim;
}

const std::pair<int,int>& Board::getXDim() {
    return m_xDim;
}

const std::pair<int,int>& Board::getYDim() {
    return m_yDim;
}

void Board::updateNeighbors(int x, int y, bool state) {
  for (int row = x - 1; row <= x + 1; row++) {
    for (int col = y - 1; col <= y + 1; col++) {
      if (row != x || col != y) {  // dont update count for the input cell itself
        Cell& neighborCell = getCell(row, col);
        neighborCell.updateNeighborCount(state);
        // std::cout << "Updating: " << getStateRep(neighborCell.getX(), neighborCell.getY(), state, true) << std::endl;

        // update drawing region
        std::pair<int, int> newXDim = m_xDim;
        std::pair<int, int> newYDim = m_yDim;

        // adjust dimension for drawing
        if (neighborCell.getX() < newXDim.first) {
          newXDim.first = neighborCell.getX();
        }
        if (neighborCell.getX() > newXDim.second) {
          newXDim.second = neighborCell.getX();
        }
        if (neighborCell.getY() < newYDim.first) {
          newYDim.first = neighborCell.getY();
        }
        if (neighborCell.getY() > newYDim.second) {
          newYDim.second = neighborCell.getY();
        }
        m_xDim = newXDim;
        m_yDim = newYDim;
      }
    }
  }
}
bool Board::setCellState(int x, int y, bool state, bool doNotUpdateNeighbors) {
    Cell& cell = getCell(x, y);
    bool oldState = cell.getState();

    if (oldState != state) {
        cell.setState(state);
        // state has changed: update count of living cells for all neighbors if state has changed
        if (!doNotUpdateNeighbors) {
            // need to defer neighbor update during board update
            updateNeighbors(x, y, state);
        }
        return true;
    }
    return false;
}

/// initialize the board with rateOfLivingCells ratio of living cells, a width of width, and a height of height
int Board::initialize(double rateOfLivingCells, std::pair<int,int> xDim, std::pair<int,int> yDim) {
    srand(time(NULL)); // init random number generator with a random seed
    int cutoff = 100 - (rateOfLivingCells * 100);
    int nbrLivingCells = 0;
    for (int i = xDim.first; i <= xDim.second; ++i) {
        for (int j = yDim.first; j <= yDim.second; ++j) {
            int randNumber = rand() % 100; // random number between 0 and 100
            bool cellState = randNumber > cutoff;
            setCellState(i, j, cellState);

            if (cellState) {
                ++nbrLivingCells;
            }
        }
    }
    return nbrLivingCells;
}

void Board::update() {
    // update should apply the rules of the game of life on every cell
    std::unordered_set<std::pair<int,int>, hash_pair> changedCells; // cells whose status was changed

    for (auto& cellEntry: m_cells) {
        Cell& cell = cellEntry.second;
        int neighborCount = cell.getLivingNeighborCount();
        bool newState = cell.getState();
        if (cell.getState()) {
            // any living cell with two or three neighbors survives
            if (neighborCount != 2 && neighborCount != 3) {
                // kill living cells that don't match criterion
                newState = false;
            }
        } else {
            // dead cell becomes alive
            if (neighborCount == 3) {
                // revive dead cell with 3 living neighbors
                newState = true;
            }
        }
        // defer updating neighbors until we have evaluated all the cells
        bool wasCellChanged = setCellState(cell.getX(), cell.getY(), newState, true);
        if (wasCellChanged) {
            changedCells.insert(std::make_pair(cell.getX(), cell.getY()));
        }
    }
    // update neighbors
    for (auto& changedCell : changedCells) {
        updateNeighbors(changedCell.first, changedCell.second, getCellState(changedCell.first, changedCell.second));
    }
}

std::string Board::toString() {
    // find min/max x, min/max y to draw the board. better: store max / min during set alive
    std::string rep = "";

    for (int x = m_xDim.first; x < m_xDim.second; ++x) {
        for (int y = m_yDim.first; y < m_yDim.second; ++y) {
            std::pair<int,int> curPos = std::make_pair(x,y);
            bool curState = false;
            if (m_cells.count(curPos) != 0) {
                Cell& curCell = m_cells[curPos];
                curState = curCell.getState();
            }
            std::string stateRep = getStateRep(x, y, curState);
            rep += stateRep;
        }
        rep += "\n";
    }
    return rep;
}

bool Board::getCellState(int x, int y) {
    return getCell(x, y).getState();

}

Cell& Board::getCell(int x, int y) {
    std::pair<int,int> pairIdx = std::make_pair(x,y);

    if (m_cells.count(pairIdx) == 0) {
        m_cells[pairIdx] = Cell(x, y, false);
    }
    return m_cells[pairIdx];
}

int Board::getCellLivingNeighborCount(int x, int y) {
    return getCell(x, y).getLivingNeighborCount();
}

