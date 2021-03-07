//
// Created by Jack Thomson on 06/03/2021.
//

#ifndef BILGING_HELPERS_HPP
#define BILGING_HELPERS_HPP

#define x_pos(x) x % 6
#define y_pos(x) x / 6

bool inline can_move(byte piece) {
    return piece < 7;
}

int inline promote_score(int count) {
    if (count == 3) return 100;
    if (count == 4) return 10000;
    return count;
}

int inline row_score(int count) {
    if (count == 3) return 3;
    if (count == 4) return 5;
    if (count == 5) return 7;

    return 0;
}

#endif //BILGING_HELPERS_HPP
