#include "InputManager.hpp"

namespace Pacenstein {
    sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) {
        return sf::Mouse::getPosition(window);
    }
}
