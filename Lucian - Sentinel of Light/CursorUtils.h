#pragma once
#ifndef CURSOR_UTILS_H
#define CURSOR_UTILS_H

#include <SFML/Graphics.hpp>

inline void updateCursor(sf::RenderWindow& window, sf::Cursor& arrow, sf::Cursor& hand, bool isHovering) {
    window.setMouseCursor(isHovering ? hand : arrow);
}

#endif