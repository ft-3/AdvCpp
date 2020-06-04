#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Window.hpp>
#include "board.hpp"
#include <boost/program_options.hpp>
#include "rle_parser.hpp"
#include "cell.hpp"

namespace po = boost::program_options;


po::variables_map handle_cmd_options(int ac, const char** av) {
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
        ("gui", po::value<bool>()->default_value(true), "Print in GUI instead of terminal window")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm); 

    if (vm.count("help")) {
        std::cout << desc << "\n";
    }
    return vm;
}

RleParser parse_rle(po::variables_map& vm) {
    RleParser fig(vm["rle"].as<std::string>());
    fig.parse();
    return fig;
}

void print_board() {
}


int main(int ac, const char** av) {

    // cmd variables handling
    // ================================================================================
    auto vm = handle_cmd_options(ac, av);

    auto C = vm["width"].as<int>();
    auto R = vm["height"].as<int>();
    auto speed = vm["speed"].as<int>();
    auto max = vm["max"].as<int>();
    auto gui = vm["max"].as<int>();
    Board game_board(R, C);



    if (vm.count("rle")) {
        auto x = vm.count("x") ? vm["x"].as<int>() : 0;
        auto y = vm.count("y") ? vm["y"].as<int>() : 0;
        game_board.apply_figure(parse_rle(vm).get_figure(), x, y);
    }

    sf::Window window;
    sf::RenderWindow render_w;

    if (gui) {
    // Calculate frame rate from speed parameter
        sf::Window window(sf::VideoMode(cell_size_px * C+4, cell_size_px * R+4), "Conway's Game of Life", sf::Style::Titlebar);
        sf::WindowHandle handle = window.getSystemHandle();
        sf::RenderWindow render_w(handle);
    }

    bool pause = false;
    int count = 0;
    sf::Time delay_time = sf::milliseconds(speed);
    bool cond = true;
    while (cond) {
        bool cond = count <= max;
        if (gui) {
            cond = cond && window.isOpen();
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) window.close();
                if (event.key.code == sf::Keyboard::P) pause = !pause;
            }
        }
        if (!pause) {
            if (gui)
                game_board.draw_board(render_w);
            else game_board.draw_board(std::cout);
            if (!game_board.step())
                break;
        }
        if (max)
            count++;
        sf::sleep(delay_time);
    }
}

