#pragma once

#include "Entity.hpp"

namespace Pacenstein {
    /**
     * Items are entities that award points.
     */
    class Item : public Entity {
    public:
        Item(const float x, const float y, unsigned int p = 0);
        Item(const sf::Vector2f xy, unsigned int p = 0);

        unsigned int getPoints();

    protected:
        const unsigned int points;
    };
}
