#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Window.hpp>
#include "board.hpp"
#include <boost/program_options.hpp>
#include "rle_parser.hpp"

namespace po = boost::program_options;

int main(int ac, const char** av) {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("width", po::value<int>()->default_value(10), "Set board width")
        ("height", po::value<int>()->default_value(10), "Set board height")
        ("speed", po::value<int>()->default_value(500), "Speed of iteration in ms")
        ("max", po::value<int>()->default_value(0), "Max number of iterations")
        ("rle", po::value<std::string>(), "Path to file with RLE encoded figure")
        ("x", po::value<int>(), "Starting x coordinate of the given figure (used only with given path)")
        ("y", po::value<int>(), "Starting y coordinate of the given figure (used only with given path)")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm); 

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    auto C = vm["width"].as<int>();
    auto R = vm["height"].as<int>();
    auto speed = vm["speed"].as<int>();
    auto max = vm["max"].as<int>();
    Board game_board(R, C);

    if (vm.count("rle")) {
        RleParser fig(vm["rle"].as<std::string>());
        try {
            fig.parse();
            for (auto row : fig.get_figure()) {
                for (auto cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            auto x = vm.count("x") ? vm["x"].as<int>() : 0;
            auto y = vm.count("y") ? vm["y"].as<int>() : 0;
            game_board.apply_figure(fig.get_figure(), x, y);
        } catch (...) {
            std::cout << "Parsing failed. Ending execution" << std::endl;
        }
    }

    using namespace std::chrono;
    auto next = steady_clock::now();
    auto prev = next - milliseconds(speed);
    int count = 0;
    while (count <= max) {
        std::cout << game_board << std::endl;
        // If no neighbors at all game ends;
        if (!game_board.step())
            break;
        auto now = steady_clock::now();
        prev = now;

        // delay until time to iterate again
        next += milliseconds(speed);
        std::this_thread::sleep_until(next);
        if (max)
            count++;
    }
}
