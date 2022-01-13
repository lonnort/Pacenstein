#pragma once

#include <SFML/System/Vector2.hpp>

namespace Pacenstein {
    class Entity {
    public:
        Entity(){}
        ~Entity(){}
    private:
	sf::Vector2f position;
	sf::Vector2f direction;
	float move_speed;
    };
}
