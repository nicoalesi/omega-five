#pragma once

#include <sstream>

#include "bitboard.hpp"
#include "common.hpp"
#include "nnue/nnue.hpp"

extern bitboard pieces[2];
extern int stm;
extern int ply_count;

void reset ();
void set_position (std::string pos);
