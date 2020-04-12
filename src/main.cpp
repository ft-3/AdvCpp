#include <iostream>
#include <thread>
#include <chrono>
#include "board.hpp"

constexpr int R = 10;
constexpr int C = 10;

int main() {
    using namespace std::chrono;
    auto next = steady_clock::now();
    auto prev = next - 500ms;
    Board game_board(R, C);
    while (true) {
        std::cout << game_board << std::endl << std::endl;
        game_board.step();
        auto now = steady_clock::now();
        prev = now;

        // delay until time to iterate again
        next += 500ms;
        std::this_thread::sleep_until(next);
    }


}
