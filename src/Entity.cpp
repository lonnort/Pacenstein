#include "Entity.hpp"

namespace Pacenstein {
    Entity::Entity(float px, float py, float dx, float dy, float sx, float sy, float ms):
        Entity({px, py}, {dx, dy}, {sx, sy}, ms)
    {}

    Entity::Entity(sf::Vector2f pos, sf::Vector2f dir, sf::Vector2f size, float ms):
        // bounding_box(size),
        position(pos),
        direction(dir),
        size(size),
        moveSpeed(ms)
    {
        // bounding_box.setPosition(pos);
        // bounding_box.setSize(sf::Vector2f(0.5, 0.5));
    }

    Entity::Entity():
        Entity(0,0,0,0,0,0,0)
    {}

    // Entity::Entity(const std::shared_ptr<Entity> entity){
    //     bounding_box = entity->bounding_box;
    //     position = entity->position;
    //     direction = entity->direction;
    //     size = entity->size;
    //     moveSpeed = entity->moveSpeed;
    // }

    sf::Vector2f Entity::getPos() { return sf::Vector2f(this->position.x, this->position.y); }
    sf::Vector2f Entity::getDir() { return sf::Vector2f(this->direction.x, this->direction.y); }

    float Entity::getPosX() { return this->position.x; }
    float Entity::getPosY() { return this->position.y; }
    float Entity::getDirX() { return this->direction.x; }
    float Entity::getDirY() { return this->direction.y; }

    // sf::FloatRect Entity::getGlobalBounds() { return bounding_box.getGlobalBounds(); }
}
