#include <iostream>
#include "board.hpp"

constexpr int R = 10;
constexpr int C = 10;

int main() {
     Board game_board(R, C);
     std::cout << game_board;
}
