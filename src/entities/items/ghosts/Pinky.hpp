#pragma once

#include "Ghost.hpp"

namespace Pacenstein {
    /**
     * The subclass for Pinky.
     *
     * Pinky is a subclass of Ghost, Pinky is the pink ghost.
     *
     * Pinky is the first of the ghosts to leave the house.
     */
    class Pinky : public Ghost {
    public:
        /**
         * Constructor of the Pinky ghost class.
         *
         * \param x The x position as a float of Pinky.
         * \param y The y position as a float of Pinky.
         */
        Pinky(float x, float y);

        /**
         * Constructor of the Pinky ghost class.
         *
         * \param xy The position of Pinky as a sf::Vector2f.
         */
        explicit Pinky(sf::Vector2f xy);

        /**
         * Returns the sprite of Pinky based on the direction and the corresponding texture.
         *
         * \param data A reference to the game data object.
         * \return An sf::Sprite of the direction of Pinky.
         */
        sf::Sprite getGhostSprite(game_data_ref_t data);

        /**
         * Moves Pinky to an new position based on the direction.
         * 
         * If Pinky hits a wall, the direction is randomly changed to a new one.
         *
         * \param worldMap A reference to the world map to detect walls.
         * \return An sf::Vector2f of the new position of Pinky.
         */
        sf::Vector2f move(const map_t & worldMap) override;

    private:
        std::vector<std::string> pinkyDirections = {    "Pinky Back One",
                                                        "Pinky Back Two",
                                                        "Pinky Left One",
                                                        "Pinky Left Two",
                                                        "Pinky Middle One",
                                                        "Pinky Middle Two",
                                                        "Pinky Right One",
                                                        "Pinky Right Two" };
                                    
        uint direction;

        sf::Sprite pinkySprite;
    };
}
