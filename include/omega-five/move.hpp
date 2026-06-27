#pragma once

#include "bitboard.hpp"
#include "board.hpp"
#include "common.hpp"
#include "pattern.hpp"
#include "nnue/nnue.hpp"

void make_move (int move);
void undo_move (int move);
move_list get_legal_moves ();
