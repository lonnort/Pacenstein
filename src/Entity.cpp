#include "Entity.hpp"

namespace Pacenstein {
    Entity::Entity(double px, double py, double sx, double sy, double dx, double dy, double ms):
        posX(px), posY(py),
        dirX(dx), dirY(dy),
        sizeX(sx), sizeY(sy),
        moveSpeed(ms)
    {}

    Entity::Entity(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f dir, double ms):
        Entity(pos.x, pos.y, size.x, size.y, dir.x, dir.y, ms)
    {}

    Entity::Entity():
        Entity(0,0,0,0,0,0,0)
    {}
}
