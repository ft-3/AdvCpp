#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
using std::vector;

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
    friend std::ostream& operator<<(std::ostream&, Board&);
};
