#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace Pacenstein {
    /**
     * The class describing what anything that can be interacted with has to contain.
     *
     * Entities are items like fruits and pellets, ghosts, and the player itself.
     */
    class Entity {
    public:
        Entity(float px, float py, float dx, float dy, float sx, float sy, float ms = 0);
        Entity(sf::Vector2f pos, sf::Vector2f dir, sf::Vector2f size, float ms = 0);
        Entity();

        sf::Vector2f getPos();
        sf::Vector2f getDir();

        sf::FloatRect getGlobalBounds();

    protected:
        sf::RectangleShape bounding_box;

    	sf::Vector2f position, direction, size;
    	float moveSpeed;
    };
}
