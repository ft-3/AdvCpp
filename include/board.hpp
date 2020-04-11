#pragma once
#include <iostream>
#include <vector>
#include <map>
using std::vector;

const std::map<bool, char> vals = { {true, 'x'}, {false, 'o'} };

struct Board {
private:
    vector<vector<bool>> cells;

public:
    Board(int, int);
    vector<vector<bool>> get_cells() const;
    friend std::ostream& operator<<(std::ostream&, Board&);
};
