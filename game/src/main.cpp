//
// Created by Sumuk Shashidhar on 1/9/23.
//


#include "board.h"
#include "agent.h"
#include "ai.h"

int main() {
    Board b;
    AI ai;
    std::cout << ai.getBestMove(b, 0) << std::endl;
}
