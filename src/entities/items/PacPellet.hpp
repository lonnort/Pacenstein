#pragma once

#include <SFML/Graphics.hpp>
#include "Item.hpp"

namespace Pacenstein {
    /**
     * PacPellets are the normal point awarding currency of the game.
     *
     * Each pellet awards 10 points and does nothing special. Collect all pellets to end the game,
     * or progress to the next stage.
     */
    class PacPellet : public Item {
    public:
        /**
         * Constructor of the PacPellet class.
         *
         * \param x The x position as a float of a pellet.
         * \param y The y position as a float of a pellet.
         */
        PacPellet(float x, float y);

        /**
         * Constructor of the PacPellet class.
         *
         * \param xy The position of a pellet as a sf::Vector2f.
         */
        explicit PacPellet(sf::Vector2f xy);

        /**
         * Interaction of a pac pellet with the player.
         *
         * Gives the player 10 points.
         *
         * \param data A reference to the data object.
         */
        void interact(game_data_ref_t data) override;
    };
}
