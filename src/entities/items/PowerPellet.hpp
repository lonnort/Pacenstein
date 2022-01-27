#pragma once

#include "Item.hpp"

namespace Pacenstein {
    /**
     * PowerPellets give bonus points and award the ability to eat ghosts.
     *
     * A PowerPellet will grant the Player 100 points, which is 10 times the amount of a regular
     * pellet. The Player will also get the ability to eat Ghosts for a short duration, each Ghost
     * eaten will also grant bonus points.
     */
    class PowerPellet : public Item {
        /**
         * Constructor of the PowerPellet class.
         *
         * \param x The x position as a float of a power pellet.
         * \param y The y position as a float of a power pellet.
         */
        PowerPellet(float x, float y);

        /**
         * Constructor of the PowerPellet class.
         *
         * \param xy The position of a power pellet as a sf::Vector2f.
         */
        explicit PowerPellet(sf::Vector2f xy);
    };
}
