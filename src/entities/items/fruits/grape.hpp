#pragma once

#include "Fruit.hpp"

namespace Pacenstein {
    /**
     * Grapes (Melons according to some) are a type of fruit and give 1000 points.
     */
    class Grape : public Fruit {
    public:
        /**
         * Constructor of the Grape class.
         *
         * \param x The x position as a float of a grape.
         * \param y The y position as a float of a grape.
         */
        Grape(float x, float y);

        /**
         * Constructor of the Grape class.
         *
         * \param xy The position of a grape as a sf::Vector2f.
         */
        explicit Grape(sf::Vector2f xy);

    };
}
