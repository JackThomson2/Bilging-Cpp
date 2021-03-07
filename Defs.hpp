//
// Created by Jack Thomson on 06/03/2021.
//

#ifndef BILGING_DEFS_HPP
#define BILGING_DEFS_HPP

#include <cstdint>

using Piece = uint_fast8_t;

const Piece BLUE_PENTAGON = 0b00000000;
const Piece GREEN_SQUARE = 0b00000001;
const Piece BLUE_CIRCLE = 0b00000010;
const Piece BREEN_OCTAGON = 0b00000011;
const Piece DARK_BLUE_SQUARE = 0b00000100;
const Piece PALE_CIRCLE = 0b00000101;
const Piece WAVY_SQUARE = 0b00000110;
const Piece CRAB = 0b00000111;
const Piece PUFFERFISH = 0b00001000;
const Piece JELLYFISH = 0b00001001;
const Piece CLEARED = 0b00001010;
const Piece NULL_PIECE = 0b11111111;

#endif //BILGING_DEFS_HPP
