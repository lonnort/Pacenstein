#include "Entity.hpp"

namespace Pacenstein {
    Entity::Entity(float px, float py, float dx, float dy, float sx, float sy, float ms):
        Entity({px, py}, {dx, dy}, {sx, sy}, ms)
    {}

    Entity::Entity(sf::Vector2f pos, sf::Vector2f dir, sf::Vector2f size, float ms):
        bounding_box(size),
        position(pos),
        direction(dir),
        size(size),
        moveSpeed(ms)
    {
        bounding_box.setPosition(pos);
    }

    Entity::Entity():
        Entity(0,0,0,0,0,0,0)
    {}

    sf::Vector2f Entity::getPos() { return sf::Vector2f(this->position.x, this->position.y); }
    sf::Vector2f Entity::getDir() { return sf::Vector2f(this->direction.x, this->direction.y); }

    double Entity::getPosX() { return this->position.x; }
    double Entity::getPosY() { return this->position.y; }
    double Entity::getDirX() { return this->direction.x; }
    double Entity::getDirY() { return this->direction.y; }

    sf::FloatRect Entity::getGlobalBounds() { return bounding_box.getGlobalBounds(); }
}
