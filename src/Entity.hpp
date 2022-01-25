#pragma once

#include <SFML/System/Vector2.hpp>

namespace Pacenstein {
    /**
     * The class describing what anything that can be interacted with has to contain.
     *
     * Entities are items like fruits and pellets, ghosts, and the player itself.
     */
    class Entity {
    public:
        /**
         * Constructor for the Entity class
         *
         * \param position The position of the entity as an sf::Vector2f.
         * \param direction The direction the entity faces as an sf::Vector2f.
         * \param moveSpeed The speed with which the entity moves as a float.
         */
        Entity(sf::Vector2f position, sf::Vector2f direction, float moveSpeed);

    protected:
    	sf::Vector2f position;
    	sf::Vector2f direction;
    	float moveSpeed;
    };
}
