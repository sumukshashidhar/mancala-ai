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
private:
    Board internal_board;
    short generateRandomMove(short player);

};


#endif //GAME_AGENT_H
