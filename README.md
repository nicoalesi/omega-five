# Omega Five

A Connect-5 agent written in C++.

Omega Five is a high-performance Connect-5 agent built around an efficient bitboard engine,
Negamax search augmented with alpha-beta pruning, and a position evaluation function.

It exposes a UCI-style communication interface, making it easy to integrate with external GUIs.

The `main` branch version uses a handcrafted evaluation function, while the `nnue` branch implementation uses an NNUE-based evaluation network.

---

## Features

- Efficient bitboard board representation
- Negamax search with alpha-beta pruning
- Incremental move generation
- NNUE evaluation (optional)
- Lightweight UCI-style communication protocol
- CMake build system

---

## Project structure

```
├─ include/
    └─ omega-five/
        ├─ nnue/
            └─ nnue.hpp
        ├─ bitboard.hpp
        ├─ board.hpp
        ├─ common.hpp
        ├─ debug.hpp
        ├─ evaluation.hpp
        ├─ interface.hpp
        ├─ main.hpp
        ├─ move.hpp
        ├─ pattern.hpp
        └─ search.hpp
├─ nnue/
    ├─ tools/
        ├─ utils/
            ├─ cross_validation.py
            ├─ dataset.py
            ├─ loss.py
            └─ model.py
        ├─ grid_search.py
        └─ train.py
    └─ weights.nnue
├─ src/
    ├─ nnue/
        └─ nnue.cpp
    ├─ bitboard.cpp
    ├─ board.cpp
    ├─ debug.cpp
    ├─ interface.cpp
    ├─ main.cpp
    ├─ move.cpp
    └─ search.cpp
├─ tests/
    ├─ test.cpp
    ├─ test.hpp
    ├─ unit_test.cpp
    └─ unit_test.hpp
├─ CMakeLists.txt
└─ README.md
```

---

## Building

The agent can be compiled in any way but it requires `gcc`.
The project includes a CMake configuration to simplify the build process:
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

To build the test suite, set the `ENABLE_TESTS` flag:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=ON ..
```

---

## Usage

When using the NNUE evaluation, copy `nnue/weights.nnue` into the same directory as the executable.

Then it can be simply run:
```
./omega_five
```

---

## O5I Protocol

Omega Five implements a simple line-based protocol inspired by UCI.

### Engine identification

```
o5i
```
Response
```
id name omega-five
id author nicoalesi
o5iok
```

### Readiness check

```
isready
```
Response
```
readyok
```

### New game

```
newgame
```
No response, resets the internal board state.

### Set position

```
position startpos moves <move> <move> <move> ...
```
No response. Custom positions can also be loaded using a FEN-inspired board notation.

### Search

```
go <depth>
```
Response
```
bestmove <move>
```
If no depth is specified, a default search depth is used. Depth values above the engine's maximum supported depth are automatically clamped.

### Evaluation

```
evaluate <depth>
```
Response
```
value <score>
```
If no depth is specified, a default search depth is used. Depth values above the engine's maximum supported depth are automatically clamped.

### Quit
```
quit
```
No response, the process stops.

---

## Board representation

The board position is represented by two bitboards, one for each player.
Moves, and in general squares, are indexed from 0 to 99 in the following way:

```
00 01 02 03 04 05 06 07 08 09
10 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
30 31 32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47 48 49
50 51 52 53 54 55 56 57 58 59
60 61 62 63 64 65 66 67 68 69
70 71 72 73 74 75 76 77 78 79
80 81 82 83 84 85 86 87 88 89
90 91 92 93 94 95 96 97 98 99
```
```
move = row * 10 + col
```

---

## Dependencies

The engine is written entirely in native C++ and has no dependencies

## Notes

- NNUE weights are stored as raw binary data and require a little-endian architecture to be read correctly.
