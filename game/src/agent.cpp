//
// Created by Sumuk Shashidhar on 1/9/23.
//
#include "agent.h"

void Agent::play_game(bool verbose) {
    // we have to play the game until there is a winner / loser
    short rounds = 0; // tracking the number of rounds
    short player = 0; // start with player 0.
    bool playable; // for testing if the move was valid
    while (rounds <= 30000) {
        if (verbose) {
            std::cout << "Running new round: " << rounds << std::endl;
        }
        // we need to try and get a random move for player one
        short move = generateRandomMove(0);
        if (move < 0) {
            // means that there is some unplayability
            // check if the game is over first
            if (internal_board.game_over()) {
                // game is over
                break;
            }
            // no moves to play, repopulate
            // we need to check if the game is over first
            internal_board.repopulate_board();
            continue;
        }
        playable = internal_board.play(0, move);
        // let us print the score
        if (verbose) {
            std::cout << "Round: " << rounds << " " << "Score: " << internal_board.get_score(0) << " " << internal_board.get_score(1) << std::endl;
        }
        // we need to flip the player. 1 if it is 0, 0 if it is 1
        player = (player + 1) % 2;
        rounds++;
    }
    // now, we need to check who won
    if (internal_board.get_score(0) > internal_board.get_score(1)) {
        // player 0 won
        std::cout << "Player 0 won!" << std::endl;
    } else {
        // player 1 won
        std::cout << "Player 1 won!" << std::endl;
    }
}

short Agent::generateRandomMove(short player) {
    // we need to use the internal board
    std::vector<short> move_list = internal_board.get_moves(player);
    if (move_list.empty()) {
        return -1;
    }
    // we need to generate a random number
    srand((unsigned) time(nullptr));
    // return the choice
    return move_list[rand() % move_list.size()];
}

Agent::Agent() = default;
