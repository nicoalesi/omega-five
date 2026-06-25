#pragma once

#if defined(_MSC_VER)
    #define ALWAYS_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define ALWAYS_INLINE inline __attribute__((always_inline))
#else
    #define ALWAYS_INLINE inline
#endif

typedef struct {
    int moves[10];
    int size = 0;

    ALWAYS_INLINE void add (const int move) {
        moves[size] = move;
        size++;
    }

    ALWAYS_INLINE int operator [] (const int index) {
        return moves[index];
    }
    
} move_list;

using bitboard = __uint128_t;

enum side { white = 0, black = 1 };
enum direction { before = 0, after = 1 };
enum pattern_type {
    row = 0,
    col = 1,
    diag = 2,
    antidiag = 3
};
