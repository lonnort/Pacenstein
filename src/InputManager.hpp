#pragma once

#include <SFML/Graphics.hpp>

namespace Pacenstein {
    class InputManager {
    public:
        InputManager(){}
        ~InputManager(){}

        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

        bool isSpriteHovered(sf::Sprite object, sf::RenderWindow& window);

        sf::Vector2i getMousePosition(sf::RenderWindow& window);
    };
}
