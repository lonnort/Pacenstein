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

    private:
    	sf::Vector2f position;
    	sf::Vector2f direction;
    	float move_speed;
    };
}
