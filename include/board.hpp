#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <type_traits>
#include "cell.hpp"
#include <SFML/Graphics.hpp>
using std::vector;

constexpr int cell_size_px = 10;
const std::map<bool, std::string> vals = { {true, "⏺"}, {false, "○"} };

struct Board {
private:
    vector<vector<bool>> cells;
    vector<vector<bool>> prev_state;
    vector<vector<bool>> copy_board();
    int R;
    int C;
    int num_neighbors(int, int);
    int bound_val(int, bool);

public:
    Board(int, int);
    vector<vector<bool>> get_cells() const;
    bool step();
    void apply_figure(vector<vector<bool>>, int, int);

    template <typename T>
    void draw_board(T& window) {
        //static_assert(std::is_base_of<std::ostream, T>::value, "T must inherit from ostream");
        //window << cells << std::endl;
    }
    void draw_board(sf::RenderWindow& window) {
        auto x = 2;
        auto y = 2;
        for (auto row : cells) {
            for (auto cell : row) {
                window.draw(Cell::get_cell(cell, x, y, cell_size_px));
                x += cell_size_px;
            }
            y += cell_size_px; x = 2;
        }
        window.display();
    }
    friend std::ostream& operator<<(std::ostream&, Board&);
};
