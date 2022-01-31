#pragma once

#include "Fruit.hpp"

namespace Pacenstein {
    /**
     * Apples are a type of fruit and give 700 points.
     */
    class Apple : public Fruit {
    public:
        /**
         * Constructor of the Apple class.
         *
         * \param x The x position as a float of an apple.
         * \param y The y position as a float of an apple.
         */
        Apple(float x, float y);

        /**
         * Constructor of the Apple class.
         *
         * \param xy The position of an apple as a sf::Vector2f.
         */
        explicit Apple(sf::Vector2f xy);

    };
}
