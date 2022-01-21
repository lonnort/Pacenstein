#pragma once

#include <SFML/System/Vector2.hpp>

#include "Entity.hpp"

namespace Pacenstein {
    /**
     *
     */
    class Player : public Entity {
    private:
    	sf::Vector2f plane;
    	// score Score;
    	unsigned int lives;
    };
}
