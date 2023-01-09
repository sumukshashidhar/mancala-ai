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

Board::Board(const short *b, const short *s) {
    // copy the board
    for (short i = 0; i < BOARD_LEN; i++) {
        board[i] = b[i];
    }
    // copy the scores
    for (short i = 0; i < BOARD_ROWS; i++) {
        scores[i] = s[i];
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

bool Board::play(short player, short pos) {
    if (!check_playability(player)) {
        collector(player);
        return false;
    }
    // now, we need to start distribution from the player's side of the board
    // now, we need to find the number of seeds in the starting position
    short seeds = board[pos];
    // now remove the num seeds?
    board[pos] = 0;
    // now, we need to distribute the seeds
    scores[player] += distribute(seeds, get_next_valid_pos(pos));
    return true;

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
    // now, we need to take the seeds from there
    // if this next pos is empty, then we need to collect from the pos after that
    if (board[pos] == 0) {
        // collect from the next position
        return collect(get_next_valid_pos(pos));
    } else {
        // if not, we need to pick up, and start to dis
        seeds = board[pos];
        board[pos] = 0;
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
    // means the square is bankrupt
    if (board[opposite_pos] < 0) {
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
    four_seed_update();
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

void Board::four_seed_update() {
    // for each side, we need to remove the seeds, if they are exactly 4
    // iterate through the first side first
    for (short i = 0; i < BOARD_WIDTH; i++) {
        if (board[i] == 4) {
            // remove the seeds
            board[i] = 0;
            // add to the score
            scores[0] += 4;
        }
    }
    // now, iterate through the other side
    for (short i = BOARD_WIDTH; i < BOARD_LEN; i++) {
        if (board[i] == 4) {
            // remove the seeds
            board[i] = 0;
            // add to the score
            scores[1] += 4;
        }
    }
}

bool Board::check_playability(short player) {
    // we need to check if the game is playable from the perspective of the particular player
    if (player == 0) {
        // we need to check until BOARD_WIDTH
        short pos = 0;
        while (pos < BOARD_WIDTH) {
            if (board[pos] > 0) {
                return true;
            }
            pos++;
        }
    } else {
        // we need to check until the board length
        short pos = BOARD_WIDTH;
        while (pos < BOARD_LEN) {
            if (board[pos] > 0) {
                return true;
            }
            pos++;
        }
    }
    return false;
}

void Board::collector(short player) {
    short score = 0;
    short pos = 0;
    if (player == 0) {
        pos = BOARD_WIDTH;
        while (pos < BOARD_LEN) {
            score += board[pos];
            board[pos] = 0;
            pos = get_next_valid_pos(pos);
        }
        scores[1] += score;
    } else {
        while (pos < BOARD_WIDTH) {
            score += board[pos];
            board[pos] = 0;
            pos = get_next_valid_pos(pos);
        }
        scores[0] += score;
    }
}

short Board::get_score(short player) {
    return scores[player];
}

short* Board::get_board() {
    return board;
}

short *Board::get_scores() {
    return scores;
}

std::vector<short> Board::get_moves(short player) {
    // for the particular player, we just need to check
    std::vector<short> options;
    if (player == 0) {
       for (short i = 0; i < BOARD_WIDTH; i++) {
           if (board[i] > 0) {
               options.push_back(i);
           }
       }
    } else {
        for (short i = BOARD_WIDTH; i < BOARD_LEN; i++) {
            if (board[i] > 0) {
                options.push_back(i);
            }
        }
    }
    return options;
}

void Board::repopulate_board() {
    // repopulate the board using the scores.
    // lets repopulate for player one first
    while (scores[0] >= 0) {
        for (short i = 0; i < BOARD_WIDTH; i++) {
            // first, make sure that we have enough points
            if (scores[0] >= NUM_SEEDS) {
                board[i] += NUM_SEEDS;
                scores[0] -= NUM_SEEDS;
            } else {
                // this is a bad situation,
                // we need to keep the score, and then bankrupt the remaining squares
                board[i] = -1;
            }
        }
        // now, we just need to break from this loop
        break;
    }
    // now, repeat this for the other side
    while (scores[1] >= 0) {
        for (short i = BOARD_WIDTH; i < BOARD_LEN; i++) {
            // first, make sure that we have enough points
            if (scores[1] >= NUM_SEEDS) {
                board[i] += NUM_SEEDS;
                scores[1] -= NUM_SEEDS;
            } else {
                // this is a bad situation,
                // we need to keep the score, and then bankrupt the remaining squares
                board[i] = -1;
            }
        }
        // now, we just need to break from this loop
        break;
    }
}

bool Board::game_over() {
    // we can do this by checking if the game
    // this function is definitely called before repopulation, so we can just check the scores
    // two conditions
    if (scores[0] < 5 && !check_playability(0)) {
        return true;
    }
    if (scores[1] < 5 && !check_playability(1)) {
        return true;
    }
    return false;
}

