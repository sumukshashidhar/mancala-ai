//
// Created by Sumuk Shashidhar on 1/9/23.
//

#include "board.h"

int main() {
    Board board;
    board.printBoard();
    board.play(0, 3);
    board.printBoard();
    std::cout << "NEW ROUND" << std::endl;
    board.play(1, 10);
    board.printBoard();
}
