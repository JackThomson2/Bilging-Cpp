//
// Created by Jack Thomson on 07/03/2021.
//

#include "Searcher.hpp"

float Search(Board board, byte max_depth, byte depth, byte move_number) {
    float score = board.swap(move_number);
    if (score < 0 || depth == 1) {
        return score;
    }

    byte actual_depth = (max_depth - depth) + 1;
    auto moves = board.inner_filter(actual_depth, score, move_number);

    float max_score;

    if (depth > 2) {
#pragma omp parallel for default(none) reduction(max:max_score) shared(board, moves, max_depth, depth)
        for (auto i = 0; i < moves.position; i++) {
            auto move = moves.moves[i];
            auto inner_score = Search(board, max_depth, depth - 1, move);
            max_score = max_score > inner_score ? max_score : inner_score;
        }
    } else {
        for (auto i = 0; i < moves.position; i++) {
            auto move = moves.moves[i];
            auto inner_score = Search(board, max_depth, depth - 1, move);
            max_score = max_score > inner_score ? max_score : inner_score;
        }
    }

    return score;
}

MoveInfo GetBestMoveList(Board& board, byte depth) {
    auto possible_moves = board.get_moves();

    auto best_score = -9999;
    auto best_move = 0;

#pragma omp parallel for default(none) reduction(max:best_score, best_move) shared(board, possible_moves, depth)
    for (auto i = 0; i < possible_moves.position; i++) {
        auto move = possible_moves.moves[i];
        auto score = Search(board, depth, depth, move);
        if (best_score < score) {
            best_move = move;
            best_score = score;
        }
    }

    return MoveInfo(best_move, best_score);
}