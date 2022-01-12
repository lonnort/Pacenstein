#pragma once

#include <SFML/Graphics.hpp>

namespace Pacenstein {
    class InputManager {
    public:
        InputManager(){}
        ~InputManager(){}

        sf::Vector2i getMousePosition(sf::RenderWindow& window);
    };
}
