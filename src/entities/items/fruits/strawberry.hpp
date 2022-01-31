#pragma once

#include "Fruit.hpp"

namespace Pacenstein {
    /**
     * Strawberries are a type of fruit and give 300 points.
     */
    class Strawberry : public Fruit {
    public:
        /**
         * Constructor of the Strawberry class.
         *
         * \param x The x position as a float of a strawberry.
         * \param y The y position as a float of a strawberry.
         */
        Strawberry(float x, float y);

        /**
         * Constructor of the Strawberry class.
         *
         * \param xy The position of a strawberry as a sf::Vector2f.
         */
        explicit Strawberry(sf::Vector2f xy);

    };
}
