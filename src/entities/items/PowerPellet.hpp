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
    public:
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

        /**
         * Interaction of a power pellet with the player.
         *
         * Gives the player 100 points and changes the state to scattering.
         *
         * \param data A reference to the data object.
         */
        void interact(game_data_ref_t data) override;
        
        /**
         * Returns if a PowerPellet is collected by the player.
         *
         * \return A bool of if the pellet is collected.
         */
        bool is_collected();

        /**
         * Returns the position of a PowerPellet.
         *
         * \return An sf::Vector2f of the position of a pellet.
         */
        sf::Vector2f getPosition();
    };
}
