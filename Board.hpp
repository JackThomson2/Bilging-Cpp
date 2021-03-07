//
// Created by Jack Thomson on 06/03/2021.
//

#ifndef BILGING_BOARD_HPP
#define BILGING_BOARD_HPP

#include <vector>
#include <cstdint>
#include <utility>
#include <iostream>
#include "Defs.hpp"

using byte = uint_fast8_t;
using sByte = int_fast8_t;

thread_local static uint_fast8_t TO_CLEAR[72];
thread_local static uint_fast8_t CLEAR_COUNT = 0;

void inline set_to_clear(byte position) {
    TO_CLEAR[CLEAR_COUNT] = position;
    ++CLEAR_COUNT;
}

void inline reset_clears() {
    CLEAR_COUNT = 0;
}

class ArrayVec {
public:
    byte moves[60];
    byte position = 0;

    inline void Push(byte piece) {
        moves[position] = piece;
        ++position;
    }
};

class Board {
private:
    void jelly(byte type);
    void remove_clears();
    void puff(byte position);
    void shift_everything();
    float clean_board();
    std::pair<bool, float> mark_clears();
    int_fast32_t get_combo(byte position);
public:
    byte board[72]{};
    byte water;

    ArrayVec get_moves();
    float swap(byte position);

    ArrayVec inner_filter(byte depth, float score, byte move_number);

    Board(std::vector<byte> new_board, byte new_water) {
        std::copy(new_board.begin(), new_board.end(), board);
        water = new_water;
    }

    Board(const Board& copy) {
        std::copy(std::begin(copy.board), std::end(copy.board), board);
        water = copy.water;
    }
};

#endif //BILGING_BOARD_HPP
