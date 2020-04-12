#pragma once
#include <iostream>
#include <vector>
#include <map>
using std::vector;

const std::map<bool, char> vals = { {true, 'x'}, {false, 'o'} };

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
    void step();
    friend std::ostream& operator<<(std::ostream&, Board&);
};
