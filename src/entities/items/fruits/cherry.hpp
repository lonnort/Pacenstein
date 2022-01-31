#pragma once

#include "Fruit.hpp"

namespace Pacenstein {
    /**
     * Cherries are a type of fruit and give 100 points.
     */
    class Cherry : public Fruit {
    public:
        /**
         * Constructor of the Cherry class.
         *
         * \param x The x position as a float of a cherry.
         * \param y The y position as a float of a cherry.
         */
        Cherry(float x, float y);

        /**
         * Constructor of the Cherry class.
         *
         * \param xy The position of a cherry as a sf::Vector2f.
         */
        explicit Cherry(sf::Vector2f xy);

    };
}
