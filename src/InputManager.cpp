#include "InputManager.hpp"

namespace Pacenstein {
    bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window) {
        if (sf::Mouse::isButtonPressed(button)) {
            sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

            if (playButtonRect.contains(sf::Mouse::getPosition(window))) return true;
        }
        return false;
    }

    bool InputManager::isSpriteHovered(sf::Sprite object, sf::RenderWindow &window) {
        sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

        if (playButtonRect.contains(sf::Mouse::getPosition(window))) return true;
        else return false;
    }

    sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) {
        return sf::Mouse::getPosition(window);
    }
}
