//
// Created by Sumuk Shashidhar on 1/9/23.
//

#ifndef GAME_AI_H
#define GAME_AI_H

#include "board.h"
#include <vector>

const int DEPTH = 15; // look 30 moves deep

class AI{
public:
    AI() = default;
    short getBestMove(Board board, short player);
    void playTheAi(Board& board);
    static short getUserPlayerChoice();
private:
    short minimax(Board board, short depth, short alpha, short beta, short player);
    short evaluate(Board board);

    void playUserMove(Board &board, short player);
};

#endif //GAME_AI_H
