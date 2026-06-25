#include "search.hpp"

const int MAX_DEPTH = 30;

int negamax (int depth, int alpha, int beta) {
    if (depth == 0) {
        return evaluate();
    }

    move_list moves = get_legal_moves();

    if (moves.size == 0) {
        return evaluate() * (1 + depth);
    }

    int best = -INT32_MAX;

    for (int i = 0; i < moves.size; i++) {
        int move = moves[i];
        make_move(move);
        int value = -negamax(depth - 1, -beta, -alpha);
        undo_move(move);

        best = std::max(best, value);
        alpha = std::max(alpha, value);

        if (alpha >= beta) break;
    }

    return best;
}

int search_best_move (int depth) {
    int best = -1;
    int max_val = -INT32_MAX;
    int alpha = -INT32_MAX;
    int beta = INT32_MAX;

    move_list moves = get_legal_moves();

    for (int i = 0; i < moves.size; i++) {
        int move = moves[i];
        make_move(move);
        int val = -negamax(depth, -beta, -alpha);
        undo_move(move);

        if (val > max_val) {
            max_val = val;
            best = move;
        }

        alpha = std::max(alpha, val);
    }

    return best;
}
