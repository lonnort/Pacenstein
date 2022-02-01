#pragma once

#include "Entity.hpp"
#include "Definitions.hpp"
#include "Game.hpp"

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
        Item(const float x, const float y, uint p = 0, bool collected = false);

        /**
         * Constructor of the Item class.
         *
         * \param xy The position of an item as a sf::Vector2f.
         * \param p The amount of points an item gives to the player. If the amount is not defined, the item gives 0 points.
         */
        explicit Item(const sf::Vector2f xy, uint p = 0, bool collected = false);

        /**
         * Returns the amount of points of an item.
         *
         * \return An unsigned int of the points.
         */
        unsigned int getPoints();

        /**
         * Virtual interact function. Implemented in the subclasses of Item.
         *
         * Interaction of an item subclass with a player.
         *
         * \param data A reference to the game data.
         */
        virtual void interact(game_data_ref_t data) = 0;

    protected:
        const unsigned int points;
        bool collected;
    };
}
