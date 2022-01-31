#pragma once

#include "Ghost.hpp"

namespace Pacenstein {
    /**
     * The subclass for Clyde.
     *
     * Clyde is a subclass of Ghost, Clyde is the orange ghost.
     *
     * Clyde is the last to leave the house. He only exists the house if a third of the pellets has been eaten.
     */

    class Clyde : public Ghost {
    public:
        /**
         * Constructor of the Clyde ghost class.
         *
         * \param x The x position as a float of Clyde.
         * \param y The y position as a float of Clyde.
         */
        Clyde(float x, float y);

        /**
         * Constructor of the Clyde ghost class.
         *
         * \param xy The position of Clyde as a sf::Vector2f.
         */
        explicit Clyde(sf::Vector2f xy);

        /**
         * Returns the sprite of Clyde based on the direction and the corresponding texture.
         *
         * \param data A reference to the game data object.
         * \return An sf::Sprite of the direction of Clyde.
         */
        sf::Sprite getGhostSprite(game_data_ref_t data);

    private:
        std::vector<std::string> clydeDirections = {    "Clyde Back One",
                                                        "Clyde Back Two",
                                                        "Clyde Left One",
                                                        "Clyde Left Two",
                                                        "Clyde Middle One",
                                                        "Clyde Middle Two",
                                                        "Clyde Right One",
                                                        "Clyde Right Two" };
                                    
        uint direction;

        sf::Sprite clydeSprite;

        //Function to change direction based on the movement of a ghost.

        //Function for ghost movement.
    };
}
