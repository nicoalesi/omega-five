#include "debug.hpp"

void print_bitboard (bitboard bboard) {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            std::cout << getbit(bboard, r * 10 + c) << " ";
        }

        std::cout << "\n";
    }
}

void print_board (bitboard pieces[2]) {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (getbit(pieces[white], r * 10 + c)) {
                std::cout << "w";
            } else if (getbit(pieces[black], r * 10 + c)) {
                std::cout << "b";
            } else {
                std::cout << ".";
            }
        }

        std::cout << "\n";
    }
}
