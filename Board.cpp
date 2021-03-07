//
// Created by Jack Thomson on 06/03/2021.
//

#include <vector>
#include "Board.hpp"
#include "Helpers.hpp"

void Board::jelly(byte type) {
    for (auto i = 0; i < 72; i++) {
        if (board[i] == type)
            set_to_clear(i);
    }
}

void Board::remove_clears() {
    for (auto i = 0; i < CLEAR_COUNT; i++) {
        board[TO_CLEAR[i]] = CLEARED;
    }
    reset_clears();
}

void Board::puff(byte position) {
    auto x = x_pos(position);

    auto up = position >= 6;
    auto down = position < 66;
    auto right = x < 5;
    auto left = x > 0;

    set_to_clear(position);

    if (up)
        set_to_clear(position - 6);
    if (down)
        set_to_clear(position + 6);
    if (left)
        set_to_clear(position - 1);
    if (right)
        set_to_clear(position + 1);

    if (up && right)
        set_to_clear(position - 5);
    if (up && left)
        set_to_clear(position - 7);
    if (down && right)
        set_to_clear(position + 7);
    if (down && left)
        set_to_clear(position + 5);

}

void Board::shift_everything() {
    for (auto x = 0; x < 6; x++) {
        auto last = 99999;
        for (auto y = 11; y >= 0; y--) {
            auto pos = (y * 6) + x;

            auto checking = board[pos];
            if (checking == CLEARED && last == 99999)
                last = y;

            if (last != 99999 && checking != CLEARED) {
                auto last_pos = (last * 6) + x;
                board[last_pos] = checking;
                board[pos] = CLEARED;
                --last;
            }
        }
    }
}

std::pair<bool, float> Board::mark_clears() {
    auto returning = false;
    auto bonus_score = 0.0;

    for (auto pos = 0; pos < 72; pos++) {
        auto piece = board[pos];

        auto x = x_pos(pos);
        auto y = y_pos(pos);

        if (piece == CRAB && y > water) {
            set_to_clear(pos);
            returning = true;
            bonus_score += water * 2;
            continue;
        }

        if (!can_move(piece)) continue;

        if (x < 4 && pos < 70 && piece == board[pos + 1] && piece == board[pos + 2]) {
            set_to_clear(pos);
            set_to_clear(pos + 1);
            set_to_clear(pos + 2);

            returning = true;
        }

        if (pos < 60 && piece == board[pos + 6] && piece == board[pos + 12]) {
            set_to_clear(pos);
            set_to_clear(pos + 6);
            set_to_clear(pos + 12);
            returning = true;
        }
    }

    return std::pair<bool, float>(returning, bonus_score);
}

int_fast32_t Board::get_combo(byte position) {
    auto x = x_pos(position);

    auto left_piece = board[position];
    auto right_piece = board[position];

    auto multi_ct = 0;

    auto left = 0;
    auto l_col = 1;
    auto right = 0;
    auto r_col = 1;

    if (x >= 2 && board[position - 1] == left_piece && board[position - 2] == left_piece) {
        left = 3;
        multi_ct = 1;
    }

    if (x < 3 && board[position + 2] == right_piece && board[position + 3] == right_piece) {
        right = 3;
        ++multi_ct;
    }

    if (position > 5 && board[position - 6] == left_piece) {
        ++l_col;
        if (position > 11 && board[position - 12] == left_piece)
            ++l_col;
    }

    if (position < 66 && board[position + 6] == left_piece) {
        ++l_col;
        if (position < 60 && board[position + 12] == left_piece)
            ++l_col;
    }

    if (position > 4 && board[position - 5] == right_piece) {
        ++r_col;
        if (position > 11 && board[position - 11] == right_piece)
            ++r_col;
    }

    if (position < 65 && board[position + 7] == right_piece) {
        ++r_col;
        if (position < 59 && board[position + 13] == right_piece)
            ++r_col;
    }

    if (r_col < 3) r_col = 0;
    if (l_col < 3) l_col = 0;

    if (r_col > 2) ++multi_ct;
    if (l_col > 2) ++multi_ct;

    if (multi_ct == 0) return 0;

    if (multi_ct == 4 && (r_col == 5 && l_col == 5))
        return 9999999; // Minus to give space for other points

    if (multi_ct == 4 && (r_col == 5 || l_col == 5))
        return 999999; // Minus to give space for other points

    return (row_score(left) + row_score(right) + row_score(l_col) + row_score(r_col)) * promote_score(multi_ct);
}

float Board::clean_board() {
    float extra_broken = 0;
    auto clear_res = mark_clears();

    while (clear_res.first) {
        extra_broken += (float)CLEAR_COUNT;
        extra_broken += clear_res.second;
        remove_clears();
        shift_everything();
        clear_res = mark_clears();
    }

    return extra_broken;
}

float Board::swap(byte position) {
    reset_clears();
    float score = 0.0;

    auto one = board[position];
    auto two = board[position + 1];

    if (one == two || one == CRAB || two == CRAB || one == CLEARED || two == CLEARED) return -3000.1;

    if (one == PUFFERFISH || two == PUFFERFISH) {
        puff(position + (one == PUFFERFISH ? 0 : 1));
        score = CLEAR_COUNT;
        remove_clears();
        shift_everything();
    } else if (one == JELLYFISH || two == JELLYFISH) {
        jelly(one == JELLYFISH ? one : two);
        score = CLEAR_COUNT;
        remove_clears();
        shift_everything();
    } else {
        board[position] = two;
        board[position + 1] = one;

        score = (float)get_combo(position);
        score += clean_board();
        return score;
    }

    score += clean_board();

    return score;
}

ArrayVec Board::get_moves() {
    ArrayVec moves;

    for (byte i = 0; i < 71; i++) {
        if (x_pos(i) == 5) continue;

        auto left = board[i];
        if (left == CLEARED || left == NULL_PIECE || left == CRAB) continue;

        auto right = board[i + 1];
        if (left == right || right == CLEARED || right == NULL_PIECE || right == CRAB) continue;

        moves.Push(i);
    }

    return moves;
}

ArrayVec Board::inner_filter(byte depth, float score, byte move_number) {
    byte start = depth > 3 ? 12 : 6;
    byte end = depth > 3 ? 48 : 60;

    ArrayVec moves;

    for (byte i = start; i < end; i++) {
        byte x_pos = x_pos(i);
        if (x_pos == 5) continue;

        if (score == 0 && move_number == i) continue;

        auto left = board[i];
        if (left == CLEARED || left == NULL_PIECE || left == CRAB) continue;

        auto right = board[i + 1];
        if (left == right || right == CLEARED || right == NULL_PIECE || right == CRAB) continue;

        auto valid_col = depth > 3 ? (x_pos < 4 && x_pos > 1) : (x_pos < 5 && x_pos > 0);
        if (!valid_col) continue;

        moves.Push(i);
    }

    return moves;
}

