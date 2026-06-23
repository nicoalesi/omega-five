#include "unit_test.hpp"

// -- Helper functions

void setup_pieces(int side, std::initializer_list<int> squares) {
    pieces[side] = 0;
    for (int sq : squares) setbit(pieces[side], sq);
}

// -- Five-piece lines tests

bool test_row_exact_five() {
    setup_pieces(white, {0, 1, 2, 3, 4});
    return count_fives(white) == 1;
}

bool test_column_exact_five() {
    setup_pieces(white, {0, 10, 20, 30, 40});
    return count_fives(white) == 1;
}

bool test_diagonal_exact_five() {
    setup_pieces(white, {0, 11, 22, 33, 44});
    return count_fives(white) == 1;
}

bool test_antidiagonal_exact_five() {
    setup_pieces(white, {9, 18, 27, 36, 45});
    return count_fives(white) == 1;
}

bool test_row_four_not_enough () {
    setup_pieces(white, {0, 1, 2, 3});
    return count_fives(white) == 0;
}

bool test_column_four_not_enough () {
    setup_pieces(white, {0, 10, 20, 30});
    return count_fives(white) == 0;
}

bool test_diagonal_four_not_enough () {
    setup_pieces(white, {0, 11, 22, 33});
    return count_fives(white) == 0;
}

bool test_antidiagonal_four_not_enough () {
    setup_pieces(white, {9, 18, 27, 36});
    return count_fives(white) == 0;
}

bool test_row_five_with_gap() {
    setup_pieces(white, {0, 1, 3, 4, 5});
    return count_fives(white) == 0;
}

bool test_column_five_with_gap() {
    setup_pieces(white, {0, 10, 30, 40, 50});
    return count_fives(white) == 0;
}

bool test_diagonal_five_with_gap() {
    setup_pieces(white, {0, 11, 33, 44, 55});
    return count_fives(white) == 0;
}

bool test_antidiagonal_five_with_gap() {
    setup_pieces(white, {9, 18, 36, 45, 54});
    return count_fives(white) == 0;
}

bool test_row_no_wraparound() {
    setup_pieces(white, {8, 9, 10, 11, 12});
    return count_fives(white) == 0;
}

bool test_diagonal_no_wraparound() {
    setup_pieces(white, {7, 18, 29, 30, 41});
    return count_fives(white) == 0;
}

bool test_antidiagonal_no_wraparound() {
    setup_pieces(white, {3, 12, 21, 30, 39});
    return count_fives(white) == 0;
}

// Fives
bool test_count_fives () {
    if (!test_row_exact_five()) return false;
    if (!test_column_exact_five()) return false;
    if (!test_diagonal_exact_five()) return false;
    if (!test_antidiagonal_exact_five()) return false;
    if (!test_row_four_not_enough()) return false;
    if (!test_column_four_not_enough()) return false;
    if (!test_diagonal_four_not_enough()) return false;
    if (!test_antidiagonal_four_not_enough()) return false;
    if (!test_row_five_with_gap()) return false;
    if (!test_column_five_with_gap()) return false;
    if (!test_diagonal_five_with_gap()) return false;
    if (!test_antidiagonal_five_with_gap()) return false;
    if (!test_row_no_wraparound()) return false;
    if (!test_diagonal_no_wraparound()) return false;
    if (!test_antidiagonal_no_wraparound()) return false;

    return true;
}

// -- End of five-piece lines tests

// -- Four-piece patterns tests

bool test_row_open_four () {
    setup_pieces(black, {}); 
    setup_pieces(white, {1, 2, 3, 4}); 
    return count_open_fours(white) == 1;
}

bool test_column_open_four () {
    setup_pieces(black, {});
    setup_pieces(white, {15, 25, 35, 45});
    return count_open_fours(white) == 1;
}

bool test_diagonal_open_four () {
    setup_pieces(black, {});
    setup_pieces(white, {11, 22, 33, 44});
    return count_open_fours(white) == 1;
}

bool test_antidiagonal_open_four () {
    setup_pieces(black, {});
    setup_pieces(white, {14, 23, 32, 41});
    return count_open_fours(white) == 1;
}

bool test_blocked_row_open_four () {
    setup_pieces(black, {10});
    setup_pieces(white, {11, 12, 13, 14});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {15});
    setup_pieces(white, {11, 12, 13, 14});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {});
    setup_pieces(white, {10, 11, 12, 13});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(white, {16, 17, 18, 19});
    if (count_open_fours(white) != 0) return false;

    return true;
}

bool test_blocked_column_open_four () {
    setup_pieces(black, {5});
    setup_pieces(white, {15, 25, 35, 45});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {55});
    setup_pieces(white, {15, 25, 35, 45});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {});
    setup_pieces(white, {0, 10, 20, 30}); 
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {});
    setup_pieces(white, {60, 70, 80, 90});
    if (count_open_fours(white) != 0) return false;

    return true;
}

bool test_blocked_diagonal_open_four () {
    setup_pieces(black, {0});
    setup_pieces(white, {11, 22, 33, 44});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {55});
    setup_pieces(white, {11, 22, 33, 44});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {});
    setup_pieces(white, {0, 11, 22, 33});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(white, {6, 17, 28, 39});
    if (count_open_fours(white) != 0) return false;

    return true;
}

bool test_blocked_antidiagonal_open_four () {
    setup_pieces(black, {4});
    setup_pieces(white, {13, 22, 31, 40});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {49});
    setup_pieces(white, {13, 22, 31, 40});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(black, {});
    setup_pieces(white, {9, 18, 27, 36});
    if (count_open_fours(white) != 0) return false;

    setup_pieces(white, {40, 49, 58, 67});
    if (count_open_fours(white) != 0) return false;

    return true;
}

bool test_row_five_is_not_open_four() {
    setup_pieces(black, {});
    setup_pieces(white, {1, 2, 3, 4, 5});
    return count_open_fours(white) == 0;
}

bool test_column_five_is_not_open_four() {
    setup_pieces(black, {});
    setup_pieces(white, {15, 25, 35, 45, 55});
    return count_open_fours(white) == 0;
}

bool test_diagonal_five_is_not_open_four() {
    setup_pieces(black, {});
    setup_pieces(white, {11, 22, 33, 44, 55});
    return count_open_fours(white) == 0;
}

bool test_antidiagonal_five_is_not_open_four() {
    setup_pieces(black, {});
    setup_pieces(white, {18, 27, 36, 45, 54});
    return count_open_fours(white) == 0;
}

// Open fours
bool test_count_open_fours () {
    if (!test_row_open_four()) return false;
    if (!test_column_open_four()) return false;
    if (!test_diagonal_open_four()) return false;
    if (!test_antidiagonal_open_four()) return false;
    if (!test_blocked_row_open_four()) return false;
    if (!test_blocked_column_open_four()) return false;
    if (!test_blocked_diagonal_open_four()) return false;
    if (!test_blocked_antidiagonal_open_four()) return false;
    if (!test_row_five_is_not_open_four()) return false;
    if (!test_column_five_is_not_open_four()) return false;
    if (!test_diagonal_five_is_not_open_four()) return false;
    if (!test_antidiagonal_five_is_not_open_four()) return false;

    return true;
}

bool test_row_four () {
    setup_pieces(black, {5});
    setup_pieces(white, {1, 2, 3, 4}); 
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {20, 22, 23, 24});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {10, 11, 13, 14});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {35, 36, 37, 39});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {0});
    setup_pieces(white, {1, 2, 3, 4});
    if (count_fours(white) != 1) return false;

    return true;
}

bool test_column_four () {
    setup_pieces(black, {63});
    setup_pieces(white, {23, 33, 43, 53});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {9, 29, 39, 49});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {54, 64, 84, 94});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {0, 10, 20, 40});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {27});
    setup_pieces(white, {37, 47, 57, 67});
    if (count_fours(white) != 1) return false;

    return true;
}

bool test_diagonal_four () {
    setup_pieces(black, {55});
    setup_pieces(white, {11, 22, 33, 44});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {20, 31, 42, 53});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {5, 16, 38, 49});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {99});
    setup_pieces(white, {44, 55, 66, 88});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {1});
    setup_pieces(white, {12, 23, 34, 45});
    if (count_fours(white) != 1) return false;

    return true;
}

bool test_antidiagonal_four () {
    setup_pieces(white, {39, 48, 57, 66});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {0}); 
    setup_pieces(white, {17, 26, 35, 53});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {7, 16, 34, 43});
    if (count_fours(white) != 1) return false;

    setup_pieces(white, {14, 32, 41, 50});
    if (count_fours(white) != 1) return false;

    setup_pieces(black, {54});
    setup_pieces(white, {18, 27, 36, 45});
    if (count_fours(white) != 1) return false;

    return true;
}

bool test_row_open_four_is_ignored () {
    setup_pieces(black, {});
    setup_pieces(white, {11, 12, 13, 14});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_column_open_four_is_ignored () {
    setup_pieces(black, {});
    setup_pieces(white, {15, 25, 35, 45});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_diagonal_open_four_is_ignored () {
    setup_pieces(black, {});
    setup_pieces(white, {11, 22, 33, 44});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_antidiagonal_open_four_is_ignored () {
    setup_pieces(black, {});
    setup_pieces(white, {27, 36, 45, 54});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_blocked_row_four () {
    setup_pieces(black, {10, 15});
    setup_pieces(white, {11, 12, 13, 14});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {4});
    setup_pieces(white, {0, 1, 2, 3});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {15});
    setup_pieces(white, {16, 17, 18, 19});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_blocked_column_four() {
    setup_pieces(black, {5, 55});
    setup_pieces(white, {15, 25, 35, 45});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {40});
    setup_pieces(white, {0, 10, 20, 30});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {50});
    setup_pieces(white, {60, 70, 80, 90});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_blocked_diagonal_four() {
    // Case: OXXXXO
    setup_pieces(black, {0, 55});
    setup_pieces(white, {11, 22, 33, 44});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {47});
    setup_pieces(white, {3, 14, 25, 36});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {52});
    setup_pieces(white, {63, 74, 85, 96});
    if (count_fours(white) != 0) return false;

    return true;
}

bool test_blocked_antidiagonal_four() {
    setup_pieces(black, {18, 63});
    setup_pieces(white, {27, 36, 45, 54});
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {58});
    setup_pieces(white, {67, 76, 85, 94}); 
    if (count_fours(white) != 0) return false;

    setup_pieces(black, {45});
    setup_pieces(white, {9, 18, 27, 36});
    if (count_fours(white) != 0) return false;

    return true;
}

// Fours
bool test_count_fours () {
    if (!test_row_four()) return false;
    if (!test_column_four()) return false;
    if (!test_diagonal_four()) return false;
    if (!test_antidiagonal_four()) return false;
    if (!test_row_open_four_is_ignored()) false;
    if (!test_column_open_four_is_ignored()) false;
    if (!test_diagonal_open_four_is_ignored()) false;
    if (!test_antidiagonal_open_four_is_ignored()) false;
    if (!test_blocked_row_four()) return false;
    if (!test_blocked_column_four()) return false;
    if (!test_blocked_diagonal_four()) return false;
    if (!test_blocked_antidiagonal_four()) return false;

    return true;
}

// -- End of four-piece patterns tests

// -- Three-piece patterns tests

bool test_row_three () {
    // __XXX
    setup_pieces(black, {});
    setup_pieces(white, {7, 8, 9});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {5});
    setup_pieces(white, {2, 3, 4});
    if (count_threes(white) != 1) return false;

    // _X_XX
    setup_pieces(black, {});
    setup_pieces(white, {6, 8, 9});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {25});
    setup_pieces(white, {21, 23, 24});
    if (count_threes(white) != 1) return false;

    // _XX_X
    setup_pieces(black, {95});
    setup_pieces(white, {91, 92, 94});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {24});
    setup_pieces(white, {26, 27, 29});
    if (count_threes(white) != 1) return false;

    // _XXX_
    setup_pieces(black, {5});
    setup_pieces(white, {1, 2, 3});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {94});
    setup_pieces(white, {96, 97, 98});
    if (count_threes(white) != 1) return false;

    // X__XX
    setup_pieces(black, {35});
    setup_pieces(white, {30, 33, 34});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {54});
    setup_pieces(white, {55, 58, 59});
    if (count_threes(white) != 1) return false;

    // X_X_X
    setup_pieces(black, {45});
    setup_pieces(white, {40, 42, 44});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {54});
    setup_pieces(white, {55, 57, 59});
    if (count_threes(white) != 1) return false;

    // X_XX_
    setup_pieces(black, {75});
    setup_pieces(white, {70, 72, 73});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {84});
    setup_pieces(white, {85, 87, 88});
    if (count_threes(white) != 1) return false;

    // XX__X
    setup_pieces(black, {15});
    setup_pieces(white, {10, 11, 14});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {24});
    setup_pieces(white, {25, 26, 29});
    if (count_threes(white) != 1) return false;

    // XX_X_
    setup_pieces(black, {34, 40});
    setup_pieces(white, {35, 36, 38});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {84});
    setup_pieces(white, {85, 86, 88});
    if (count_threes(white) != 1) return false;

    // XXX__
    setup_pieces(black, {});
    setup_pieces(white, {0, 1, 2});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {10});
    setup_pieces(white, {11, 12, 13});
    if (count_threes(white) != 1) return false;

    return true;
}

bool test_column_three () {
    // __XXX
    setup_pieces(black, {});
    setup_pieces(white, {70, 80, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {50});
    setup_pieces(white, {20, 30, 40});
    if (count_threes(white) != 1) return false;

    // _X_XX
    setup_pieces(black, {});
    setup_pieces(white, {60, 80, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {55});
    setup_pieces(white, {15, 35, 45});
    if (count_threes(white) != 1) return false;

    // _XX_X
    setup_pieces(black, {55});
    setup_pieces(white, {15, 25, 45});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {51});
    setup_pieces(white, {11, 21, 41});
    if (count_threes(white) != 1) return false;

    // _XXX_
    setup_pieces(black, {50});
    setup_pieces(white, {10, 20, 30});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {31, 91});
    setup_pieces(white, {51, 61, 71});
    if (count_threes(white) != 1) return false;

    // X__XX
    setup_pieces(black, {55});
    setup_pieces(white, {5, 35, 45});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {54});
    setup_pieces(white, {4, 34, 44});
    if (count_threes(white) != 1) return false;

    // X_X_X
    setup_pieces(black, {56});
    setup_pieces(white, {6, 26, 46});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {48});
    setup_pieces(white, {58, 78, 98});
    if (count_threes(white) != 1) return false;

    // X_XX_
    setup_pieces(black, {});
    setup_pieces(white, {2, 22, 32});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {41});
    setup_pieces(white, {51, 71, 81});
    if (count_threes(white) != 1) return false;

    // XX__X
    setup_pieces(black, {58});
    setup_pieces(white, {8, 18, 48});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {43});
    setup_pieces(white, {53, 63, 93});
    if (count_threes(white) != 1) return false;

    // XX_X_
    setup_pieces(black, {});
    setup_pieces(white, {0, 10, 30});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {46});
    setup_pieces(white, {56, 66, 86});
    if (count_threes(white) != 1) return false;

    // XXX__
    setup_pieces(black, {40});
    setup_pieces(white, {50, 60, 70});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {57});
    setup_pieces(white, {7, 17, 27});
    if (count_threes(white) != 1) return false;

    return true;
}

bool test_diagonal_three () {
    // __XXX
    setup_pieces(black, {});
    setup_pieces(white, {77, 88, 99});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {55});
    setup_pieces(white, {22, 33, 44});
    if (count_threes(white) != 1) return false;

    // _X_XX
    setup_pieces(black, {});
    setup_pieces(white, {66, 88, 99});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {59});
    setup_pieces(white, {15, 37, 48});
    if (count_threes(white) != 1) return false;

    // _XX_X
    setup_pieces(black, {});
    setup_pieces(white, {66, 77, 99});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {58});
    setup_pieces(white, {14, 25, 47});
    if (count_threes(white) != 1) return false;

    // _XXX_
    setup_pieces(black, {55});
    setup_pieces(white, {11, 22, 33});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {33, 99});
    setup_pieces(white, {55, 66, 77});
    if (count_threes(white) != 1) return false;

    // X__XX
    setup_pieces(black, {});
    setup_pieces(white, {0, 33, 44});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {40});
    setup_pieces(white, {51, 84, 95});
    if (count_threes(white) != 1) return false;

    // X_X_X
    setup_pieces(black, {});
    setup_pieces(white, {0, 22, 44});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {55, 77, 99});
    if (count_threes(white) != 1) return false;

    // X_XX_
    setup_pieces(black, {});
    setup_pieces(white, {0, 22, 33});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {43});
    setup_pieces(white, {54, 76, 87});
    if (count_threes(white) != 1) return false;

    // XX__X
    setup_pieces(black, {});
    setup_pieces(white, {0, 11, 44});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {30});
    setup_pieces(white, {41, 52, 85});
    if (count_threes(white) != 1) return false;

    // XX_X_
    setup_pieces(black, {});
    setup_pieces(white, {0, 11, 33});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {4});
    setup_pieces(white, {15, 26, 48});
    if (count_threes(white) != 1) return false;

    // XXX__
    setup_pieces(black, {});
    setup_pieces(white, {0, 11, 22});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {34});
    setup_pieces(white, {45, 56, 67});
    if (count_threes(white) != 1) return false;

    return true;
}

bool test_antidiagonal_three () {
    // __XXX
    setup_pieces(black, {45});
    setup_pieces(white, {54, 63, 72});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {4, 13, 22});
    if (count_threes(white) != 1) return false;

    // _X_XX
    setup_pieces(black, {45});
    setup_pieces(white, {54, 63, 81});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {4, 13, 31});
    if (count_threes(white) != 1) return false;

    // _XX_X
    setup_pieces(black, {49});
    setup_pieces(white, {58, 76, 85});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {9, 63});
    setup_pieces(white, {18, 36, 45});
    if (count_threes(white) != 1) return false;

    // _XXX_
    setup_pieces(black, {45});
    setup_pieces(white, {63, 72, 81});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {13, 22, 31});
    if (count_threes(white) != 1) return false;

    // X__XX
    setup_pieces(black, {});
    setup_pieces(white, {54, 63, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {9, 18, 45});
    if (count_threes(white) != 1) return false;

    // X_X_X
    setup_pieces(black, {});
    setup_pieces(white, {54, 72, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {9, 27, 45});
    if (count_threes(white) != 1) return false;

    // X_XX_
    setup_pieces(black, {});
    setup_pieces(white, {63, 72, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {33, 42, 60});
    if (count_threes(white) != 1) return false;

    // XX__X
    setup_pieces(black, {});
    setup_pieces(white, {54, 81, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {});
    setup_pieces(white, {9, 36, 45});
    if (count_threes(white) != 1) return false;

    // XX_X_
    setup_pieces(black, {});
    setup_pieces(white, {63, 81, 90});
    if (count_threes(white) != 1) return false;

    setup_pieces(black, {70});
    setup_pieces(white, {34, 52, 61});
    if (count_threes(white) != 1) return false;

    // XXX__
    setup_pieces(black, {});
    setup_pieces(white, {72, 81, 90});
    if (count_threes(white) != 1) return false;

    // anchor=40, piece:40 piece:31 piece:22 empty:13 empty:4, top blocked by opponent
    setup_pieces(black, {53});
    setup_pieces(white, {26, 35, 44});
    if (count_threes(white) != 1) return false;

    return true;
}

// Threes
bool test_count_threes () {
    if (!test_row_three()) return false;
    if (!test_column_three()) return false;
    if (!test_diagonal_three()) return false;
    if (!test_antidiagonal_three()) return false;

    return true;
}

// -- End of three-piece patterns tests

// -- Test manager

void run_unit_tests () {
    if (test_count_fives()) {
        std::cout << "[+] Test [count_fives]\n";
    } else {
        std::cout << "[x] Test [count_fives]\n";
    }

    if (test_count_open_fours()) {
        std::cout << "[+] Test [count_open_fours]\n";
    } else {
        std::cout << "[x] Test [count_open_fours]\n";
    }

    if (test_count_fours()) {
        std::cout << "[+] Test [count_fours]\n";
    } else {
        std::cout << "[x] Test [count_fours]\n";
    }

    if (test_count_threes()) {
        std::cout << "[+] Test [count_threes]\n";
    } else {
        std::cout << "[x] Test [count_threes]\n";
    }
}
