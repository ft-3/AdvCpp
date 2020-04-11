#include <iostream>
#include <vector>
#include <map>
#include "board.hpp"
#include "range.hpp"
using util::lang::indices;
using std::vector;

Board::Board(int rows, int cols) {
    cells = vector<vector<bool>>(rows);
    for (auto i : indices(cells))
        cells[i] = vector<bool>(cols);
}

vector<vector<bool>> Board::get_cells() const { return cells; }

std::ostream& operator<<(std::ostream& os, vector<bool>& row) {
    for (auto val : row)
        os << vals.at(val);
    return os;
}

std::ostream& operator<<(std::ostream& os, Board& brd) {
    for (auto row : brd.get_cells())
        os << row << std::endl;
    return os;
}

