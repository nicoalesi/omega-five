cmake_minimum_required(VERSION 3.15)
project(OmegaFive VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -O3 -march=native)

option(ENABLE_TESTS "Build the testing executable" OFF)

# Core engine library
add_library(omega_five_core
    src/bitboard.cpp
    src/board.cpp
    src/debug.cpp
    src/interface.cpp
    src/move.cpp
    src/search.cpp
    src/nnue/nnue.cpp
)

target_include_directories(omega_five_core PUBLIC include/omega-five)

# Main executable
add_executable(omega_five src/main.cpp)
target_link_libraries(omega_five PRIVATE omega_five_core)

# Testing executable
if (ENABLE_TESTS)
    add_executable(omega_five_tests
        tests/test.cpp
        tests/unit_test.cpp
    )

    target_link_libraries(omega_five_tests PRIVATE omega_five_core)
endif()
