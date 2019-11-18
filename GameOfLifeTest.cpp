#include <iostream>
using namespace std;

#include <gtest/gtest.h>
#include "Board.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

struct TestClass : public testing::Test {
};

TEST_F(TestClass, BoardValueSet) {
    Board b;
    b.setCellState(0, 0, true);
    ASSERT_EQ(b.getCellState(0,0), true);
}

TEST_F(TestClass, BoardValueReset) {
    Board b;
    b.setCellState(0, 0, true);
    b.setCellState(0, 0, false);
    ASSERT_EQ(b.getCellState(0,0), false);
}

TEST_F(TestClass, CellLivingNeighborCountOne) {
    Board b;
    b.setCellState(0, 0, true);

    // cell itself has zero neighbors alive
    ASSERT_EQ(b.getCellLivingNeighborCount(0,0), 0);
    // neighbors have one alive cell
    ASSERT_EQ(b.getCellLivingNeighborCount(0,1), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(0,-1), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,-1), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,0), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,1), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,1), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,0), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,-1), 1);
    // other cell not in neighborhood of 0,0 has no alive neighbors
    ASSERT_EQ(b.getCellLivingNeighborCount(1,-2), 0);
}

TEST_F(TestClass, CellLivingNeighborCountOneReset) {
    Board b;
    b.setCellState(0, 0, true);
    // after double resetting to dead: 0 neighbors alive
    b.setCellState(0, 0, false);
    b.setCellState(0,0, false);
    ASSERT_EQ(b.getCellLivingNeighborCount(0,1), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(0,0), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(0,-1), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,-1), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,0), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,1), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,1), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,0), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,-1), 0);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,-2), 0);
}

TEST_F(TestClass, CellLivingNeighborCountTwo) {
    Board b;
    b.setCellState(0, 0, true);
    b.setCellState(0, 1, true);

    // state is: 1 1
    // check that neighborhood is 2 or 1, depending on proximity
    ASSERT_EQ(b.getCellLivingNeighborCount(0,1), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(0,0), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,1), 2);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,0), 2);
    ASSERT_EQ(b.getCellLivingNeighborCount(1,2), 1);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,1), 2);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,0), 2);
    ASSERT_EQ(b.getCellLivingNeighborCount(-1,2), 1);
}

TEST_F(TestClass, testBoardInitialization) {
    Board b;
    // build initial 10 x 10 board, with approximately 75% living cells
    double rateOfLivingCells = 0.75;
    int width = 10;
    int height = 10;
    int nbrOfLivingCells = b.initialize(rateOfLivingCells, std::make_pair(1, width), std::make_pair(1,height));
    std::cout << "nbr of living cells is: " << nbrOfLivingCells << std::endl;
    ASSERT_GE(nbrOfLivingCells, 0.5 * (width*height));
}

TEST_F(TestClass, testBoardUpdate) {
    Board b;
    b.setCellState(0, 0, true);
    b.setCellState(0, 1, true);
    b.setCellState(0, 2, true);
    // state: 1 1 1
    // expect that dead cell with 3 neighbors becomes alive after update
    b.update();
    // test other points:
    ASSERT_TRUE(b.getCellState(1, 1)); // cell in the middle should be alive now: has 3 neighbors
    ASSERT_FALSE(b.getCellState(1, 2)); // cell to the right should remain dead: only 2 neighbors
    ASSERT_FALSE(b.getCellState(1, 0)); // cell to the left should remain dead: only 2 neighbors

    // test points themselves:
    ASSERT_FALSE(b.getCellState(0,0)); // cell had only 1 neighbor, should be dead
    ASSERT_TRUE(b.getCellState(0,1)); // cell had 2 neighbor, should be alive
    ASSERT_FALSE(b.getCellState(0,2)); // cell had only 1 neighbor, should be dead
}

