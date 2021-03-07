//
// Created by Jack Thomson on 06/03/2021.
//

#ifndef BILGING_SEARCHER_HPP
#define BILGING_SEARCHER_HPP

#include "Board.hpp"
#include <vector>

class MoveInfo {
public:
    byte move;
    float score;

    MoveInfo(byte moves, float scores) {
        move = moves;
        score = scores;
    }
};

using MoveList = std::vector<MoveInfo>;

float Search(Board board, byte max_depth, byte depth, byte move_number);

MoveInfo GetBestMoveList(Board& board, byte depth);

#endif //BILGING_SEARCHER_HPP
