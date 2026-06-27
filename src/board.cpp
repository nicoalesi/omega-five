#include "board.hpp"

bitboard pieces[2];
int stm;
int ply_count;

void reset () {
    pieces[white] = 0;
    pieces[black] = 0;
    stm = white;
    ply_count = 0;
}

void set_position (std::string pos) {
    reset();

    std::istringstream ss(pos);
    std::string token;
    ss >> token;

    // Set board
    // [0, 9]: number of empty positions
    // a: ten empty positions (whole row empty)
    // w: white piece
    // b: black piece

    int i = 0;
    for (const char &c : token) {
        if (c == '/') {
            continue;
        }

        if (0 <= (c - '0') && (c - '0') <= 9) {
            i += (c - '0');
            continue;
        }

        if (c == 'a') {
            i += 10;
            continue;
        }

        if (c == 'w') {
            setbit(pieces[white], i);
            ply_count++;
            update_accumulators(i, ply_count, white);
            i++;
            continue;
        }

        if (c == 'b') {
            setbit(pieces[black], i);
            ply_count++;
            update_accumulators(i, ply_count, black);
            i++;
            continue;
        }
    }

    ss >> token;
    stm = (token != "w");

    ss >> token;
    ply_count = std::stoi(token);
}
