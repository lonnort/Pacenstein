#include "Entity.hpp"

namespace Pacenstein{
    Entity::Entity(sf::Vector2f position, sf::Vector2f direction, float moveSpeed):
        position(position),
        direction(direction),
        moveSpeed(moveSpeed)
    {}
}