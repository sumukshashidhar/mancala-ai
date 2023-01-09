//
// Created by Sumuk Shashidhar on 1/9/23.
//
#include "board.h"

Board::Board() {
    // fill the board with the required number of seeds
    for (short & i : board) {
        i = NUM_SEEDS;
    }
    // set the scores to 0
    for (short & i : scores) {
        i = 0;
    }
}

void Board::printBoard() {
    // print the board in a reverse fashion
    for (short i = BOARD_LEN - 1; i >= 0; i--) {
        std::cout << board[i] << " ";
        if (i == BOARD_WIDTH) {
            std::cout << std::endl;
            break;
        }
    }
    for (short i = 0; i < BOARD_LEN; i++) {
        std::cout << board[i] << " ";
        if (i == BOARD_WIDTH - 1) {
            std::cout << std::endl;
            break;
        }
    }
    // print the scores
    std::cout << "Scores: " << scores[0] << " " << scores[1] << std::endl;
}

void Board::play(short player, short pos) {
    // now, we need to start distribution from the player's side of the board
    // now, we need to find the number of seeds in the starting position
    short seeds = board[pos];
    // now remove the num seeds?
    board[pos] = 0;
    // now, we need to distribute the seeds
    scores[player] = distribute(seeds, get_next_valid_pos(pos));
    // print
//    printBoard();

}

short Board::distribute(short seeds, short pos) {
    // okay, now, we need to iterate the distribution.
    while (seeds > 0) {
        // we can distribute
        board[pos]++;
        seeds--;
        pos = get_next_valid_pos(pos);
    }
    // it ends at some point. we need to figure out WHY it ended first.
    // we have to check for certain things first
//    // we just need to pick up the seeds from the next valid pos
//    pos = get_next_valid_pos(pos);
    // now, we need to take the seeds from there
    // if this next pos is empty, then we need to collect from the pos after that
    if (board[pos] == 0) {
        // collect from the next position
        return collect(get_next_valid_pos(pos));
    } else {
        // if not, we need to pick up, and start to dis
        seeds = board[pos];
        board[pos] = 0;
        // re-distribute
//        printBoard();
        return distribute(seeds, get_next_valid_pos(pos));
    }
}

short Board::collect(short pos) {
    // we need to collect the seeds at pos, and the opposite side of pos
    // we know that pos exists.
    short seed_store = board[pos];
    // let us now negate the seeds here
    board[pos] = 0;
    // let us also get the seeds on the opposite side of pos
    short opposite_pos = BOARD_LEN - pos - 1;
    if (board[opposite_pos] < 0) {
        // means the square is bankrupt
        return seed_store;
    }
    seed_store += board[opposite_pos];
    board[opposite_pos] = 0;
    // now, let us return the picked number of seeds
    return seed_store;
}

short Board::get_next_valid_pos(short pos) {
    // for a given position, generates the next position, by ignoring all the
    // piggies and bankrupt squares
    karu_update();
    if (pos == BOARD_LEN) {
        // now, we need to first reset to 0
        pos = 1;
    } else if (pos == BOARD_LEN - 1) {
        pos = 0;
    }
    else {
        pos += 1;
    }
    while (board[pos] < 0) {
        pos += 1;
    }
    // now, we come the point where board[pos] is 0 or +ve, so it is valid
    return pos;
}

void Board::karu_update() {
    // for each side, we need to remove the seeds, if they are exactly 4
    // iterate through the first side first
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (board[i] == 4) {
            // remove the seeds
            board[i] = 0;
            // add to the score
            scores[0] += 4;
        }
    }
    // now, iterate through the other side
    for (int i = BOARD_WIDTH; i < BOARD_LEN; i++) {
        if (board[i] == 4) {
            // remove the seeds
            board[i] = 0;
            // add to the score
            scores[1] += 4;
        }
    }
}

void Board::check_playability(short player) {
    // we need to check if the game is playable from the perspective of the player
}
