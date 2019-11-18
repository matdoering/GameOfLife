#include "Board.h"
#include <curses.h> // for clearing the screen
#include <unistd.h>

int main(int argc, char **argv) {
    Board board;
    board.setDrawingRegion(std::make_pair(-20, 20), std::make_pair(-30, 30));
    board.initialize(0.75, std::make_pair(-10, 10), std::make_pair(-10,10));
    initscr(); // init curses screen

    int nbrOfIterations = 1000;
    for (int i = 0; i < nbrOfIterations; ++i) {
        std::string rep = board.toString();
        rep = "Iteration: " + std::to_string(i)  + "\n" + rep;
        addstr(rep.c_str());
        refresh();
        usleep(100000);
        erase(); // remove previous curses output
        board.update();
    }
    endwin(); // restore previous screen
	return 0;
}


