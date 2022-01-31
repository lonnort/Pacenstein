#pragma once

#include "Fruit.hpp"

namespace Pacenstein {
    /**
     * Peaches (Oranges according to some) are a type of fruit and give 500 points.
     */
    class Peach : public Fruit {
    public:
        /**
         * Constructor of the Peach class.
         *
         * \param x The x position as a float of a peach.
         * \param y The y position as a float of a peach.
         */
        Peach(float x, float y);

        /**
         * Constructor of the Peach class.
         *
         * \param xy The position of a peach as a sf::Vector2f.
         */
        explicit Peach(sf::Vector2f xy);

    };
}
