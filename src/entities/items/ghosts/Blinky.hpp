#pragma once

#include "Ghost.hpp"
#include <vector>
#include <string>

namespace Pacenstein {
    /**
     * The subclass for Blinky.
     *
     * Blinky is a subclass of Ghost, Blinky is the red ghost.
     *
     * Blinky is the most aggresive ghost, as he tries to make a beeline,
     * to the player immediately.
     */
    class Blinky : public Ghost {
    public:
        /**
         * Constructor of the Blinky ghost class.
         *
         * \param x The x position as a float of Blinky.
         * \param y The y position as a float of Blinky.
         */
        Blinky(float x, float y);

        /**
         * Constructor of the Blinky ghost class.
         *
         * \param xy The position of Blinky as a sf::Vector2f.
         */
        explicit Blinky(sf::Vector2f xy);

        /**
         * Returns the sprite of blinky based on the direction and the corresponding texture.
         *
         * \param data A reference to the game data object.
         * \return An sf::Sprite of the direction of Blinky.
         */
        sf::Sprite getGhostSprite(game_data_ref_t data);

        /**
         * 
         * 
         */
        sf::Vector2f move(const map_t & worldMap) override;

    private:
        std::vector<std::string> blinkyDirections = {   "Blinky Back One",
                                                        "Blinky Back Two",
                                                        "Blinky Left One",
                                                        "Blinky Left Two",
                                                        "Blinky Middle One",
                                                        "Blinky Middle Two",
                                                        "Blinky Right One",
                                                        "Blinky Right Two" };
                                    
        uint direction = 1;

        sf::Sprite blinkySprite;

        //Function to change direction based on the movement of a ghost.

        //Function for ghost movement.
    };
}
