#pragma once

#include "common.hpp"
#include "evaluation.hpp"
#include "move.hpp"

extern const int MAX_DEPTH;

int negamax (int depth, int alpha, int beta);
int search_best_move (int depth);
