//
// Created by Sumuk Shashidhar on 1/9/23.
//

#ifndef GAME_AGENT_H
#define GAME_AGENT_H

#include "board.h"

class Agent {
public:
    Agent();
    void play_game(bool verbose = false);
    // reset game functionality
    void reset_game();
    // play with random agent!
    void playWithRandomAgent();
private:
    Board internal_board;
    short generateRandomMove(short player);
    bool noMovesLeft();
    short moveConverter(short move);
    void playUserMove(short player);
};


#endif //GAME_AGENT_H
