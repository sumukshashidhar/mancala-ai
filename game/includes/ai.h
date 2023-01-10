//
// Created by Sumuk Shashidhar on 1/9/23.
//

#ifndef GAME_AI_H
#define GAME_AI_H

#include "board.h"
#include <vector>

const int DEPTH = 30; // look 30 moves deep

class AI{
public:
    AI() = default;
    short getBestMove(Board board, short player);
private:
    short minimax(Board board, short depth, short alpha, short beta, short player);
    short evaluate(Board board);
};

#endif //GAME_AI_H
