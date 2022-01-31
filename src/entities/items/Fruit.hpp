#pragma once

#include "Item.hpp"

namespace Pacenstein {
    /**
     * Fruits are a type of item that give bonus points.
     *
     * Fruits give bonus points and will always spawn in the center of the map. There are several
     * different fruits, ranging from strawberries to apples, each worth different amounts of
     * points. Unlike the PowerPellet, Fruit does not grant the ability to eat a Ghost.
     */
    class Fruit : public Item {
    public:
        /**
         * Constructor of the Fruit class.
         *
         * \param x The x position as a float of a fruit.
         * \param y The y position as a float of a fruit.
         * \param p The points given for a certain fruit.
         */
        Fruit(const float x, const float y, uint p = 0);

        /**
         * Constructor of the Fruit class.
         *
         * \param xy The position of a fruit as a sf::Vector2f.
         * \param p The points given for a certain fruit.
         */
        explicit Fruit(const sf::Vector2f xy, uint p = 0);

        /**
         * Interaction of a fruit with the player.
         *
         * Adds the points of a fruit to the score of the player.
         *
         * \param data A reference to the game data.
         */
        void interact(game_data_ref_t data) override;

    };
}
