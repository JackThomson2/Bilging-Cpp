//
// Created by Jack Thomson on 07/03/2021.
//

#ifndef BILGING_GENERATOR_HPP
#define BILGING_GENERATOR_HPP

#include <vector>
#include "Board.hpp"

const std::string TEST_BOARD = "342425566242255233236626363325325654445364556566465626325643654263463456";

Piece inline CharToPiece(char incoming) {
    return incoming - 48;
}

std::vector<Piece> StringToPieceArr(const std::string& incoming) {
    std::vector<Piece> pieces;
    pieces.reserve(incoming.length());

    for (char character: incoming) {
        pieces.push_back(CharToPiece(character));
    }

    return pieces;
}

Board GenerateABoard(const std::string& incoming) {
    auto pieces = StringToPieceArr(incoming);

    return Board(pieces, 4);
}

Board MakeTestBoard() {
    return GenerateABoard(TEST_BOARD);
}


#endif //BILGING_GENERATOR_HPP
