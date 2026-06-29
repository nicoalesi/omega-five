#pragma once

#include "bitboard.hpp"
#include "board.hpp"
#include "common.hpp"
#include "nnue/nnue.hpp"
#include "pattern.hpp"

ALWAYS_INLINE int evaluate () {
    if (count_fives(stm)) {
        return 10000;
    }

    if (count_fives(!stm)) {
        return -10000;
    }

    int8_t hl1_output[HIDDEN_L1_SIZE];
    for (int i = 0; i < HIDDEN_L1_SIZE; i++) {
        hl1_output[i] = activation(acc_stack[ply_count][stm][i], HIDDEN_L1_SHIFT);
    }

    int32_t hl2_output[HIDDEN_L2_SIZE];
    for (int i = 0; i < HIDDEN_L2_SIZE; i++) {
        int32_t sum = model.hl2_biases[i];
        for (int j = 0; j < HIDDEN_L1_SIZE; j++) {
            sum += hl1_output[j] * model.hl2_weights[i * HIDDEN_L1_SIZE + j];
        }

        hl2_output[i] = activation(sum, HIDDEN_L2_SHIFT);
    }

    int32_t output = model.ol_bias;
    for (int i = 0; i < HIDDEN_L2_SIZE; i++) {
        output += hl2_output[i] * model.ol_weights[i];
    }

    return output >> OUTPUT_SHIFT;
}
