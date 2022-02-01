#pragma once

#include "Item.hpp"

namespace Pacenstein {
    /**
     * Ghosts are item that move around on their own volition.
     *
     * Every ghost has a different AI for attacking the Player. Every ghost is capable of deducting
     * a life from the player, unless the player has eaten a PowerPellet, then the ghosts will
     * scatter and flee from the player. If the player were to eat a ghost in this state points are
     * awarded based on how many ghosts were eaten: 200 for the first, then 400, 800, and 1600 last.
     */
    class Ghost : public Item {
    public:
        /**
         * Constructor of the Ghost class.
         *
         * \param x The x position as a float of a ghost.
         * \param y The y position as a float of a ghost.
         */
        Ghost(float x, float y);

        /**
         * Constructor of the Ghost class.
         *
         * \param xy The position of a ghost as a sf::Vector2f.
         */
        explicit Ghost(sf::Vector2f xy);

        /**
         * Interaction of a ghost with the player.
         *
         * Removes 1 live from the player.
         *
         * \param data A reference to the data object.
         */
        void interact(game_data_ref_t data) override;

        virtual sf::Vector2f move();
    };
}
