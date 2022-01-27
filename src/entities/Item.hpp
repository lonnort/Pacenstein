#pragma once

#include "Entity.hpp"
#include "Definitions.hpp"

namespace Pacenstein {
    /**
     * Items are entities that award points.
     */
    class Item : public Entity {
    public:
        /**
         * Constructor of the Item class.
         *
         * \param x The x position as a float of an item.
         * \param y The y position as a float of an item.
         * \param p The amount of points an item gives to the player. If the amount is not defined, the item gives 0 points.
         */
        Item(const float x, const float y, uint p = 0);

        /**
         * Constructor of the Item class.
         *
         * \param xy The position of an item as a sf::Vector2f.
         * \param p The amount of points an item gives to the player. If the amount is not defined, the item gives 0 points.
         */
        explicit Item(const sf::Vector2f xy, uint p = 0);

        /**
         * Returns the amount of points of an item.
         *
         * \return An unsigned int of the points.
         */
        unsigned int getPoints();

    protected:
        const unsigned int points;
    };
}
