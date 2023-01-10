//
// Created by Sumuk Shashidhar on 1/9/23.
//
#include "ai.h"

short AI::getBestMove(Board board, short player) {
    // let us make a list of moves first
    std::vector<short> possible_moves = board.get_moves(player);
    // then make a var to store the best possible move
    short best_move = possible_moves[0];
    if (player == 0) {
        short best_score = -10000;
        // now, iterate through all possible moves
        for (auto& move: possible_moves) {
            // Generate a board
            Board new_board = board;
            // make the move
            new_board.play(player, move);
            // get the score
            short score = minimax(new_board, DEPTH, 1);
            // if the score is better than the best score, update the best score
            std::cout << "Score for move " << move << " is " << score << std::endl;
            if (score > best_score) {
                best_score = score;
                best_move = move;
            }
        }
    }
    if (player == 1) {
        short best_score = 10000;
        // now, iterate through all possible moves
        for (auto& move: possible_moves) {
            // Generate a board
            Board new_board = board;
            // make the move
            new_board.play(player, move);
            // get the score
            short score = minimax(new_board, DEPTH, 0);
            std::cout << "Score for move " << move << " is " << score << std::endl;
            // if the score is better than the best score, update the best score
            if (score < best_score) {
                best_score = score;
                best_move = move;
            }
        }
    }
    return best_move;
}

short AI::minimax(Board board, short depth, short player) {
    short best_score = 0;
    if (depth == 0 || board.game_over()) {
        return evaluate(board);
    }
    std::vector<short> possible_moves = board.get_moves(player);
    if (player == 0) {
        best_score = -10000;
        for (auto& move: possible_moves) {
            Board new_board = board;
            new_board.play(player, move);
            short score = minimax(new_board, depth - 1, 1);
            if (score > best_score) {
                best_score = score;
            }
        }
    } else {
        best_score = 10000;
        for (auto& move: possible_moves) {
            Board new_board = board;
            new_board.play(player, move);
            short score = minimax(new_board, depth - 1, 0);
            if (score < best_score) {
                best_score = score;
            }
        }
    }
    return best_score;
}

short AI::evaluate(Board board) {
    // to evaluate a certain board, we do the following:
    // 1. player 0s score is pure positive
    // 2. player 1s score is pure negative
    // 3. every bankruptcy for a player is worth 10 points to the other player
    // 4. the number of pieces they have on their side of the board is multiplied by 0.5
    short eval_score = 0;
    // let us add the player 0 score first
    eval_score += 10 * board.get_score(0);
    // now let us add the player 1 score
    eval_score -= 10 * board.get_score(1);
    // this is a good starting point. let us continue later on
    return eval_score;
}
