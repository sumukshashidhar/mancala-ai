//
// Created by Sumuk Shashidhar on 1/9/23.
//

#include "board.h"
#include <cstdlib>

void play_infinite() {
    Board b;
    int rounds = 0;
    bool test;
    // Providing a seed value
    srand((unsigned) time(nullptr));
    while (true) {
        test = b.play(0, rand() % 7);
        if (!test) {
            break;
        }
        rounds++;
        test = b.play(1, rand() % 7);
        if (!test) {
            break;
        }
        rounds++;
        // print scores now
        std::cout << "Scores: " << b.get_score(0) << " " << b.get_score(1) << std::endl;
    }
    // print scores now
    std::cout << "Scores: " << b.get_score(0) << " " << b.get_score(1) << std::endl;
    // print num rounds played
    std::cout << "Rounds: " << rounds << std::endl;
}

int main() {
    play_infinite();
}
