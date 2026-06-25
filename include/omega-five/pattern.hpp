#pragma once

#include "bitboard.hpp"
#include "board.hpp"
#include "common.hpp"

ALWAYS_INLINE int count_fives (int side) {
    int rows = countbits(
        pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
    );

    int columns = countbits(
        pieces[side]
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
    );

    int diagonals = countbits(
        pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
    );

    int antidiagonals = countbits(
        pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
    );

    return rows + columns + diagonals + antidiagonals;
}

ALWAYS_INLINE int count_open_fours (int side) {
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int rows = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & ((not_occ & not_c5_mask) >> 5)
    );

    int columns = countbits(
        not_occ
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & (not_occ >> 50)
    );

    int diagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & ((not_occ & not_c5_mask) >> 55)
    );

    int antidiagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & ((not_occ & not_c5_mask) << 45)
    );

    return rows + columns + diagonals + antidiagonals;
}

ALWAYS_INLINE int count_row_fours (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[row][before] | ~(pieces[side] << 1);
    bitboard block2 = block_masks[row][after] | ~(pieces[side] >> 5);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int rows;
    int count = 0;

    // X_XXX
    rows = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // XX_XX
    rows = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((not_occ & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // XXX_X
    rows = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((not_occ & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // Edge or opponent
    block1 = block_masks[row][before] | (pieces[!side] << 1);
    block2 = block_masks[row][after] | (pieces[!side] >> 5);

    // XXXX_
    rows = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((not_occ & not_c4_mask) >> 4)
    );

    count += rows;

    // _XXXX
    rows = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;
    
    return count;
}

ALWAYS_INLINE int count_column_fours (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[col][before] | ~(pieces[side] << 10);
    bitboard block2 = block_masks[col][after] | ~(pieces[side] >> 50);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int columns;
    int count = 0;

    // X_XXX
    columns = countbits(
        block1
        & pieces[side]
        & (not_occ >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // XX_XX
    columns = countbits(
        block1
        & pieces[side]
        & (pieces[side] >> 10)
        & (not_occ >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // XXX_X
    columns = countbits(
        block1
        & pieces[side]
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (not_occ >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // Edge or opponent
    block1 = block_masks[col][before] | (pieces[!side] << 10);
    block2 = block_masks[col][after] | (pieces[!side] >> 50);

    // XXXX_
    columns = countbits(
        block1
        & pieces[side]
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (not_occ >> 40)
    );

    count += columns;

    // _XXXX
    columns = countbits(
        not_occ
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    return count;
}

ALWAYS_INLINE int count_diagonal_fours (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[diag][before] | ~(pieces[side] << 11);
    bitboard block2 = block_masks[diag][after] | ~(pieces[side] >> 55);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int diagonals;
    int count = 0;

    // X_XXX
    diagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // XX_XX
    diagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((not_occ & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // XXX_X
    diagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((not_occ & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // Edge or opponent
    block1 = block_masks[diag][before] | (pieces[!side] << 11);
    block2 = block_masks[diag][after] | (pieces[!side] >> 55);

    // XXXX_
    diagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((not_occ & not_c4_mask) >> 44)
    );

    count += diagonals;

    // _XXXX
    diagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    return count;
}

ALWAYS_INLINE int count_antidiagonal_fours (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[antidiag][before] | ~(pieces[side] >> 9);
    bitboard block2 = block_masks[antidiag][after] | ~(pieces[side] << 45);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int antidiagonals;
    int count = 0;

    // X_XXX
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // XX_XX
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((not_occ & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // XXX_X
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((not_occ & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // Edge, opponent or space
    block1 = block_masks[antidiag][before] | (pieces[!side] >> 9);
    block2 = block_masks[antidiag][after] | (pieces[!side] << 45);

    // XXXX_
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((not_occ & not_c4_mask) << 36)
    );

    count += antidiagonals;

    // _XXXX
    antidiagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    return count;
}

ALWAYS_INLINE int count_fours (int side) {
    int count = 0;

    count += count_row_fours(side);
    count += count_column_fours(side);
    count += count_diagonal_fours(side);
    count += count_antidiagonal_fours(side);

    return count;
}

ALWAYS_INLINE int count_row_threes (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[row][before] | ~(pieces[side] << 1);
    bitboard block2 = block_masks[row][after] | ~(pieces[side] >> 5);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int rows;
    int count = 0;

    // __XXX
    rows = countbits(
        not_occ
        & ((not_occ & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // _X_XX
    rows = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((not_occ & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // _XX_X
    rows = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((not_occ & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // _XXX_
    rows = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((not_occ & not_c4_mask) >> 4)
    );

    count += rows;

    // X__XX
    rows = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 1)
        & ((not_occ & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // X_X_X
    rows = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((not_occ & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // X_XX_
    rows = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((not_occ & not_c4_mask) >> 4)
    );

    count += rows;

    // XX__X
    rows = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((not_occ & not_c2_mask) >> 2)
        & ((not_occ & not_c3_mask) >> 3)
        & ((pieces[side] & not_c4_mask) >> 4)
        & block2
    );

    count += rows;

    // XX_X_
    rows = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((not_occ & not_c2_mask) >> 2)
        & ((pieces[side] & not_c3_mask) >> 3)
        & ((not_occ & not_c4_mask) >> 4)
    );

    count += rows;

    // XXX__
    rows = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 1)
        & ((pieces[side] & not_c2_mask) >> 2)
        & ((not_occ & not_c3_mask) >> 3)
        & ((not_occ & not_c4_mask) >> 4)
    );

    count += rows;

    return count;
}

ALWAYS_INLINE int count_column_threes (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[col][before] | ~(pieces[side] << 1);
    bitboard block2 = block_masks[col][after] | ~(pieces[side] >> 5);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int columns;
    int count = 0;

    // __XXX
    columns = countbits(
        not_occ
        & (not_occ >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // _X_XX
    columns = countbits(
        not_occ
        & (pieces[side] >> 10)
        & (not_occ >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // _XX_X
    columns = countbits(
        not_occ
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (not_occ >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // _XXX_
    columns = countbits(
        not_occ
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (not_occ >> 40)
    );

    count += columns;

    // X__XX
    columns = countbits(
        block1
        & pieces[side]
        & (not_occ >> 10)
        & (not_occ >> 20)
        & (pieces[side] >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // X_X_X
    columns = countbits(
        block1
        & pieces[side]
        & (not_occ >> 10)
        & (pieces[side] >> 20)
        & (not_occ >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // X_XX_
    columns = countbits(
        block1
        & pieces[side]
        & (not_occ >> 10)
        & (pieces[side] >> 20)
        & (pieces[side] >> 30)
        & (not_occ >> 40)
    );

    count += columns;

    // XX__X
    columns = countbits(
        block1
        & pieces[side]
        & (pieces[side] >> 10)
        & (not_occ >> 20)
        & (not_occ >> 30)
        & (pieces[side] >> 40)
        & block2
    );

    count += columns;

    // XX_X_
    columns = countbits(
        block1
        & pieces[side]
        & (pieces[side] >> 10)
        & (not_occ >> 20)
        & (pieces[side] >> 30)
        & (not_occ >> 40)
    );

    count += columns;

    // XXX__
    columns = countbits(
        block1
        & pieces[side]
        & (pieces[side] >> 10)
        & (pieces[side] >> 20)
        & (not_occ >> 30)
        & (not_occ >> 40)
    );

    count += columns;
    return count;
}

ALWAYS_INLINE int count_diagonal_threes (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[diag][before] | ~(pieces[side] << 1);
    bitboard block2 = block_masks[diag][after] | ~(pieces[side] >> 5);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int diagonals;
    int count = 0;

    // __XXX
    diagonals = countbits(
        not_occ
        & ((not_occ & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // _X_XX
    diagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((not_occ & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // _XX_X
    diagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((not_occ & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // _XXX_
    diagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((not_occ & not_c4_mask) >> 44)
    );

    count += diagonals;

    // X__XX
    diagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 11)
        & ((not_occ & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // X_X_X
    diagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((not_occ & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // X_XX_
    diagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((not_occ & not_c4_mask) >> 44)
    );

    count += diagonals;

    // XX__X
    diagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((not_occ & not_c2_mask) >> 22)
        & ((not_occ & not_c3_mask) >> 33)
        & ((pieces[side] & not_c4_mask) >> 44)
        & block2
    );

    count += diagonals;

    // XX_X_
    diagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((not_occ & not_c2_mask) >> 22)
        & ((pieces[side] & not_c3_mask) >> 33)
        & ((not_occ & not_c4_mask) >> 44)
    );

    count += diagonals;

    // XXX__
    diagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) >> 11)
        & ((pieces[side] & not_c2_mask) >> 22)
        & ((not_occ & not_c3_mask) >> 33)
        & ((not_occ & not_c4_mask) >> 44)
    );

    count += diagonals;

    return count;
}

ALWAYS_INLINE int count_antidiagonal_threes (int side) {
    // Edge, opponent or space
    bitboard block1 = block_masks[row][before] | ~(pieces[side] << 1);
    bitboard block2 = block_masks[row][after] | ~(pieces[side] >> 5);
    bitboard not_occ = ~(pieces[white] | pieces[black]) & bb_mask;

    int antidiagonals;
    int count = 0;

    // __XXX
    antidiagonals = countbits(
        not_occ
        & ((not_occ & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // _X_XX
    antidiagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) << 9)
        & ((not_occ & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // _XX_X
    antidiagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((not_occ & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // _XXX_
    antidiagonals = countbits(
        not_occ
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((not_occ & not_c4_mask) << 36)
    );

    count += antidiagonals;

    // X__XX
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) << 9)
        & ((not_occ & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // X_X_X
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((not_occ & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // X_XX_
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((not_occ & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((not_occ & not_c4_mask) << 36)
    );

    count += antidiagonals;

    // XX__X
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((not_occ & not_c2_mask) << 18)
        & ((not_occ & not_c3_mask) << 27)
        & ((pieces[side] & not_c4_mask) << 36)
        & block2
    );

    count += antidiagonals;

    // XX_X_
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((not_occ & not_c2_mask) << 18)
        & ((pieces[side] & not_c3_mask) << 27)
        & ((not_occ & not_c4_mask) << 36)
    );

    count += antidiagonals;

    // XXX__
    antidiagonals = countbits(
        block1
        & pieces[side]
        & ((pieces[side] & not_c1_mask) << 9)
        & ((pieces[side] & not_c2_mask) << 18)
        & ((not_occ & not_c3_mask) << 27)
        & ((not_occ & not_c4_mask) << 36)
    );

    count += antidiagonals;

    return count;
}

ALWAYS_INLINE int count_threes (int side) {
    int count = 0;

    count += count_row_threes(side);
    count += count_column_threes(side);
    count += count_diagonal_threes(side);
    count += count_antidiagonal_threes(side);

    return count;
}
