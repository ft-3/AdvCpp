#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include "range.hpp"
using util::lang::range;
using std::vector;

// RLE parser implemented as a state machine
template<class T> void ignore( const T& ) { }

enum states {
    // Skip current line
    NONE,
    X,
    Y,
    NUMBER
};


struct RleParser {
private:
    std::string filename;
    std::ifstream file;
    int width;
    int height;
    vector<vector<bool>> figure;
    const std::map<char, bool> conv = {{'b', false}, {'o', true}};

public:
    RleParser(std::string f) : filename(f), file(f) {}

    vector<vector<bool>> get_figure() const {
        return figure;
    }

    void init_figure() {
        figure = vector<vector<bool>>(height);
        for (auto& vec : figure)
            vec = vector<bool>(width);
    }

    void read_xy(std::string line) {
        auto state = X;
        auto x = std::string("");
        auto y = std::string("");
        for (auto ch : line) {
            switch (ch) {
            case ',':
                state = NONE;
                break;
            case 'y':
                state = Y;
                break;
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9': 
                if (state == X)
                    x += ch;
                else if (state == Y)
                    y += ch;
            default:
                break;
            }
        }
        width = std::stoi(x);
        height = std::stoi(y);
        init_figure();
    }

    void parse() {
        using std::string;
        string line;
        auto cur_line = 0;
        auto field = 0;
        while(std::getline(file, line)) {
            if (line[0] == '#') {}
            else if (line[0] == 'x') read_xy(line);
            else {
                auto state = NONE;
                auto mult = std::string("");
                for (auto ch : line) {
                    switch (ch) {
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9': 
                        if (state == NONE) {
                            state = NUMBER;
                            mult = std::string("") + ch;
                            std::cout << mult << std::endl;
                        }
                        else {
                            mult += ch;
                        }
                    break;
                    case '$':
                        if (state == NUMBER)
                            for (auto i : range(0, std::stoi(mult))) {
                                ignore(i);
                                cur_line++;
                            }
                        else cur_line++;
                        state = NONE;
                        field = 0;
                    break;
                    case '!':
                        state = NONE;
                        break;
                    case 'o':
                    case 'b':
                        if (state == NUMBER) {
                            state = NONE;
                            for (auto i : range(0, std::stoi(mult))) {
                                ignore(i);
                                figure[cur_line][field++] = conv.at(ch);
                            }
                        }
                        else if (state == NONE)
                            figure[cur_line][field++] = conv.at(ch);
                    break;
                    }
                }
            }
        }
    }
};
