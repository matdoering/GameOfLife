# GameOfLife

A C++ implementation of Conway's Game of Life. 

* Implementation of an "infinite" game board
* Results are displayed using the curses library
* Tests are implemented using gunit

## Build Instructions

Run the following in the source folder:

* cmake ./
* make

To run an instance of the game of life execute

* ./GameOfLife

Here, 1's indicate living cells and 0's indicate dead cells.

To run the tests, execute

* ./GameOfLifeTest

