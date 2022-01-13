#pragma once

#include <SFML/System/Vector2.hpp>

#include "../Entity.hpp"

namespace Pacenstein {
    class Player : Entity {
    public:
        Player(){}
        ~Player(){}
    private:
	sf::Vector2f plane;
	// score Score;
	unsigned int lives;
    };
}
