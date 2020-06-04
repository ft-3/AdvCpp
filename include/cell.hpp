#pragma once
#include <SFML/Graphics.hpp>


struct Cell {
public:
    static sf::RectangleShape get_cell(bool state, float px, float py, float size) {
        sf::Color alive = sf::Color(255, 255, 255);
        sf::Color dead = sf::Color(0, 0, 0);
        sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(size, size));
        rec.setPosition(px, py);
        rec.setFillColor(state ? alive : dead);

        rec.setOutlineThickness(2);
        rec.setOutlineColor(sf::Color(255,255,255));
        return rec;
    }
};
