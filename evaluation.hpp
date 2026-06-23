#pragma once

#include "bitboard.hpp"
#include "board.hpp"
#include "common.hpp"
#include "pattern.hpp"

extern const int WEIGHTS[10][10];

extern const int FIVES_SCORE;
extern const int OPEN_FOURS_SCORE;
extern const int FOURS_SCORE;
extern const int THREES_SCORE;

ALWAYS_INLINE int evaluate_side (int side) {
    int score = 0;

    score += count_fives(side) * FIVES_SCORE;

    if (score > 0) {
        return score;
    }

    if (ply_count == 100) {
        return 0;
    }

    score += count_open_fours(side) * OPEN_FOURS_SCORE;
    score += count_fours(side) * FOURS_SCORE;
    score += count_threes(side) * THREES_SCORE;

    bitboard pieces_copy = pieces[side];

    while (pieces_copy) {
        int index = getlsb(pieces_copy);;
        score += WEIGHTS[index / 10][index % 10];
        popbit(pieces_copy, index);
    }

    return score;
}

ALWAYS_INLINE int evaluate () {
    return evaluate_side(stm) - (evaluate_side(!stm) * 12) / 10;
}
