# pragma once

#include <cstdint>
#include <cstring>
#include <fstream>

#include "common.hpp"

constexpr const int INPUT_SIZE = 200;
constexpr const int HIDDEN_L1_SIZE = 1024;
constexpr const int HIDDEN_L2_SIZE = 64;

constexpr const int HIDDEN_L1_SHIFT = 20;
constexpr const int HIDDEN_L2_SHIFT = 7;
constexpr const int OUTPUT_SHIFT = 7;

constexpr const int STACK_DEPTH = 100;

struct alignas(64) NNUE {
    // Hidden layer 1 (Feature transformer)
    int32_t hl1_weights[INPUT_SIZE * HIDDEN_L1_SIZE];
    int32_t hl1_biases[HIDDEN_L1_SIZE];

    // Hidden layer 2
    int8_t hl2_weights[HIDDEN_L1_SIZE * HIDDEN_L2_SIZE];
    int32_t hl2_biases[HIDDEN_L2_SIZE];

    // Output layer
    int8_t ol_weights[HIDDEN_L2_SIZE];
    int32_t ol_bias;
};

extern NNUE model;
extern int32_t acc_stack[STACK_DEPTH][2][HIDDEN_L1_SIZE];

void init_nnue ();

ALWAYS_INLINE int8_t activation (int32_t sum, int shift) {
    int32_t scaled = sum >> shift;
    return (int8_t)(std::min(std::max(scaled, 0), 127));
}

ALWAYS_INLINE void update_accumulators (int move, int depth, int side) {
    std::memcpy(acc_stack[depth], acc_stack[depth - 1], sizeof(acc_stack[depth]));

    for (int i = 0; i < HIDDEN_L1_SIZE; i++) {
        acc_stack[depth][side][i] += model.hl1_weights[move * INPUT_SIZE + i];
        acc_stack[depth][!side][i] += model.hl1_weights[(move + 100) * INPUT_SIZE + i];
    }
}
