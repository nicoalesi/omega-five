#include "bitboard.hpp"

bitboard move_masks[10];
bitboard block_masks[4][2];

bitboard bb_mask;
bitboard not_c1_mask;
bitboard not_c2_mask;
bitboard not_c3_mask;
bitboard not_c4_mask;
bitboard not_c5_mask;

// Generate bit-masks to use during evaluation
void generate_eval_masks () {
    // Iterate over all indices
    for (int i = 0; i < 100; i++) {
        // Set all bits but the ones belonging to the first column (0)
        if (i % 10) {
            not_c1_mask |= ((bitboard)1 << i);
        }

        // Set all bits but the ones belonging columns 0, 1
        if (i % 10 > 1) {
            not_c2_mask |= ((bitboard)1 << i);
        }

        // Set all the bits but the ones belonging to columns 0, 1, 2
        if (i % 10 > 2) {
            not_c3_mask |= ((bitboard)1 << i);
        }

        // Set all the bits but the ones belonging to columns 0, 1, 2, 3
        if (i % 10 > 3) {
            not_c4_mask |= ((bitboard)1 << i);
        }

        // Set all the bits but the ones belonging to columns 0, 1, 2, 3, 4
        if (i % 10 > 4) {
            not_c5_mask |= ((bitboard)1 << i);
        }
    }

    // Set all the bits with indices [0, 99]
    bb_mask = ((bitboard)1 << 100) - 1;
}

// Generate bit-masks to use during evaluation
void generate_block_masks () {
    // Set 10 bits of each mask
    for (int i = 0; i < 10; i++) {
        // Set bits belonging to the first column (0)
        setbit(block_masks[row][before], i * 10);
        // Set bits belonging to the sixth column (5)
        setbit(block_masks[row][after], i * 10 + 5);

        // Set bits belonging to the first row (0)
        setbit(block_masks[col][before], i);
        // Set bits belonging to the sixth row (5)
        setbit(block_masks[col][after], 50 + i);

        // Set bits belonging to the last row (9)
        setbit(block_masks[antidiag][before], 90 + i);
        // Set bits belonging to the fifth row (4)
        setbit(block_masks[antidiag][after], 40 + i);
    }

    // Set bits belonging to either the first column (0) or the first row (0)
    block_masks[diag][before] |= block_masks[row][before] | block_masks[col][before];
    // Set bits belonging to either the sixth column (5) or the sixth row (5)
    block_masks[diag][after] |= block_masks[row][after] | block_masks[col][after];

    // Set bits belonging to either the last row (9) or the first column (0)
    block_masks[antidiag][before] |= block_masks[row][before];
    // Set bits belonging to either the fifth row (4) or the sixth column (5)
    block_masks[antidiag][after] |= block_masks[row][after];
}

// Generate bit-masks to use during move generation
void generate_move_masks () {
    // Iterate over columns
    for (int c = 0; c < 10; c++) {
        move_masks[c] = 0;

        // Iterate over rows
        for (int r = 0; r < 10; r++) {
            // Set all bits belonging to column c
            setbit(move_masks[c], r * 10 + c);
        }
    }
}

void init () {
    generate_eval_masks();
    generate_block_masks();
    generate_move_masks();
}
