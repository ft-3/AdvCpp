#include <iostream>
#include <vector>
#include <map>
#include "board.hpp"
#include "range.hpp"
using util::lang::indices;
using util::lang::range;
using std::vector;

void Board::apply_figure(vector<vector<bool>> fig, int x=0, int y=0) {
    for (auto i : range(y, (int)(y+fig.size())))
        for (auto j : range(x, (int)(x+fig[0].size())))
            cells[i][j] = fig[i-y][j-x];
}

Board::Board(int rows, int cols) : R(rows), C(cols) {
    cells = vector<vector<bool>>(rows);
    for (auto i : indices(cells))
        cells[i] = vector<bool>(cols);
}

vector<vector<bool>> Board::get_cells() const { return cells; }

// Creates a copy of the board to make the step a simoulteanous
// operation for all the cells
vector<vector<bool>> Board::copy_board() {
    vector<vector<bool>> previous_state(cells.size());
    for (auto i : indices(cells))
        previous_state[i] = cells[i];
    return previous_state;
}

// Bounds value so even after if goes of  the board it circles around to
// to other side. Works on horizontal and verical
int Board::bound_val(int val, bool vertical=false) {
    int max = C;
    if (vertical) max = R;

    if (val < 0) return max + val;
    else return val % max;
}

// Counts the number of neighbors for a cell with given coords
int Board::num_neighbors(int i, int j) {
    int sum = 0;
    // If the cell is alive don't count itself
    if (prev_state[i][j]) sum = -1;
    for (auto a : range(-1, 2))
        for (auto b : range(-1, 2)) {
            if (prev_state[bound_val(i-a,true)][bound_val(j-b)])
                sum++;
        }
    return sum;
}


bool Board::step() {
    prev_state = copy_board();
    auto all_neighbors = 0;
    // Iterate over entire board
    for (auto i : indices(prev_state))
        for (auto j : indices(prev_state[i])) {
            // Count number of neighbors
            auto neighbors = num_neighbors(i, j);
            all_neighbors += neighbors;
            if (prev_state[i][j]) {
                if (neighbors != 2 && neighbors != 3)
                    cells[i][j] = false;
            }
            else if (neighbors == 3) cells[i][j] = true;
        }
    return (bool) all_neighbors;
}

//int rown = 0;
// Helper functions to print board
std::ostream& operator<<(std::ostream& os, vector<bool>& row) {
    //std::cout << (rown++ % 10) << " ";
    for (auto val : row)
        os << vals.at(val) << " ";
    return os;
}

std::ostream& operator<<(std::ostream& os, Board& brd) {
    //std::cout << "  ";
    //for (auto i : range(0, 10)) std::cout << i << " ";
    std::cout << std::endl;
    for (auto row : brd.get_cells())
        os << row << std::endl;
    return os;
}

