//
// Created by Sumuk Shashidhar on 1/9/23.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>
#include <vector>

const short BOARD_ROWS = 2;
const short BOARD_WIDTH = 7;
const short BOARD_LEN = BOARD_WIDTH * BOARD_ROWS;
const short NUM_SEEDS = 5;

class Board {
public:
    // default constructor
    Board();
    // constructor based on another board (for minimax computations)
    Board(const short* b, const short* s);
    // print the state of the board for the user
    void printBoard();
    // play a move for a particular player
    bool play(short player, short pos);
    // to get the scores
    short get_score(short player);
    // to get the state of the board
    short* get_board();
    // get the score array
    short* get_scores();
    // get all possible moves for the scenario!
    std::vector<short> get_moves(short player);
    // repopulate the board
    void repopulate_board();
    // check game over
    bool game_over();
    short get_bankruptcy_score();
private:
    // store as a 1d array, for easier iterations and faster computation
    short board[BOARD_LEN]{};
    short scores[BOARD_ROWS]{};
    short distribute(short seeds, short pos);
    short get_next_valid_pos(short pos);
    void four_seed_update();
    bool check_playability(short player);
    short collect(short pos);
    void collector(short player);


};

#endif //GAME_BOARD_H
