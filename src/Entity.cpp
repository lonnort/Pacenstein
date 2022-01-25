#include "Entity.hpp"

namespace Pacenstein {
    Entity::Entity(float px, float py, float sx, float sy, float dx, float dy, float ms):
        Entity({px, py}, {sx, sy}, {dx, dy}, ms)
    {}

    Entity::Entity(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f dir, float ms):
        bounding_box(size),
        position(pos),
        size(size),
        direction(dir),
        moveSpeed(ms)
    {
        bounding_box.setPosition(pos);
    }

    Entity::Entity():
        Entity(0,0,0,0,0,0,0)
    {}

    sf::FloatRect Entity::getGlobalBounds() { return bounding_box.getGlobalBounds(); }
}
