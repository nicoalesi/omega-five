#include "move.hpp"

void make_move (int move) {
    setbit(pieces[stm], move);
    ply_count++;
    update_accumulators(move, ply_count, stm);
    stm ^= 1;
}

void undo_move (int move) {
    popbit(pieces[!stm], move);
    stm ^= 1;
    ply_count--;
}

move_list get_legal_moves () {
    static constexpr int columns[] = {4, 5, 3, 6, 2, 7, 1, 8, 0, 9};

    move_list moves;

    if (count_fives(white) > 0 || count_fives(black) > 0) {
        return moves;
    }

    if (ply_count == 100) {
        return moves;
    }

    for (int c : columns) {
        bitboard column = (pieces[white] | pieces[black]) & move_masks[c];
        int top_piece = (column) ? getlsb(column) : 100 + c;

        if (top_piece - 10 >= 0) {
            moves.add(top_piece - 10);
        }
    }

    return moves;
}
