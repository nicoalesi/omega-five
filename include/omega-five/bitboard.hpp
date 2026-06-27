#pragma once

#include <cstdint>

#include "common.hpp"

extern bitboard move_masks[10];
extern bitboard block_masks[4][2];

extern bitboard bb_mask;
extern bitboard not_c1_mask;
extern bitboard not_c2_mask;
extern bitboard not_c3_mask;
extern bitboard not_c4_mask;
extern bitboard not_c5_mask;

void init_bitboards ();

ALWAYS_INLINE void setbit (bitboard &board, int index) {
    board |= ((bitboard)1 << index);
}

ALWAYS_INLINE void popbit (bitboard &board, int index) {
    board ^= ((bitboard)1 << index);
}

ALWAYS_INLINE int getbit (bitboard board, int index) {
    return (board >> index) & 1;
}

ALWAYS_INLINE int countbits (bitboard board) {
    #if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
        board &= bb_mask;
        uint64_t low = (uint64_t)board;
        uint64_t high = (uint64_t)(board >> 64);

        return __builtin_popcountll(low) + __builtin_popcountll(high);
    #else
        int count = 0;

        board &= bb_mask;
        while (board) {
            count++;
            board &= board - 1;
        }

        return count;
    #endif
}

// Get the index of the least significant bit
ALWAYS_INLINE int getlsb (bitboard board) {
    uint64_t low = (uint64_t)board;

    if (low) {
        return __builtin_ctzll(low);
    } else {
        return 64 + __builtin_ctzll((uint64_t)(board >> 64));
    }
}
