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
        internal_board.play(0, move);
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

void Agent::reset_game() {
    // we need to reset the internal board
    internal_board = Board();
}

void Agent::playWithRandomAgent() {
    // helps you play a game with a random agent, which generates random moves!
    // we need to play the game until there is a winner / loser
    short rounds = 0; // tracking the number of rounds
    short player = 0; // start with player 0.
    // first, we need to ask the user which player he wants to be
    short user_player;
    std::cout << "Which player do you want to be? 0 or 1?" << std::endl;
    std::cin >> user_player;
    // check if we are player 0
    if (user_player == 0) {
        // we need to play the user move first
        playUserMove(0);
        // flip the player
        player = (user_player + 1) % 2;
    }
    while (true) {
        // we use the computer to now play the move
        short move = generateRandomMove(player);
        if (move < 0 && noMovesLeft()) {
            // we just lost in this case??
            std::cout << "The computer lost!" << std::endl;
            break;
        }
        // tell the user about what it is picking
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Computer picked: " << moveConverter(move) << std::endl;
        // let us make the move
        internal_board.play(player, move);
        // change the player
        player = (user_player + 1) % 2;
        // play user move
        playUserMove(player);
        // flip player
        player = (user_player + 1) % 2;
    }
    
}

bool Agent::noMovesLeft() {
    // what happens when we get move < 0
    if (internal_board.game_over()) {
        // game is over
        return true;
    } else {
        // repopulate the board. take care of it.
        internal_board.repopulate_board();
    }
    return false;
}

void Agent::playUserMove(short player) {
     // ask for a move
    internal_board.printBoard();
    // ask the user for a move choice
    short move_choice;
    std::cout << "Enter your move choice: " << std::endl;
    std::cin >> move_choice;
    // play the move
    internal_board.play(0, move_choice);
    // the board is now:
    internal_board.printBoard();
}

short Agent::moveConverter(short move) {
    // convert the move into a "readable notation"
    if (move > BOARD_WIDTH) {
        return BOARD_LEN - move;
    }
    return move;
}

Agent::Agent() = default;
