//
// Created by Sumuk Shashidhar on 1/9/23.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>

const short BOARD_ROWS = 2;
const short BOARD_WIDTH = 7;
const short BOARD_LEN = BOARD_WIDTH * BOARD_ROWS;
const short NUM_SEEDS = 5;

class Board {
public:
    Board();
    void printBoard();
    void play(short player, short pos);
private:
    // store as a 1d array, for easier iterations and faster computation
    short board[BOARD_LEN]{};
    short scores[BOARD_ROWS]{};
    short distribute(short seeds, short pos);
    short get_next_valid_pos(short pos);
    void karu_update();
    bool check_playability(short player);
    short collect(short pos);
    void collector(short player);
};

#endif //GAME_BOARD_H
