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
        Blinky(float x, float y, float speed = 0.05);

        /**
         * Constructor of the Blinky ghost class.
         *
         * \param xy The position of Blinky as a sf::Vector2f.
         */
        explicit Blinky(sf::Vector2f xy, float speed = 0.05);

        /**
         * Returns the sprite of blinky based on the direction and the corresponding texture.
         *
         * \param data A reference to the game data object.
         * \return An sf::Sprite of the direction of Blinky.
         */
        sf::Sprite getGhostSprite(game_data_ref_t data);

        /**
         * Moves Blinky to an new position based on the direction.
         * 
         * If Blinky hits a wall, the direction is randomly changed to a new one.
         *
         * \param worldMap A reference to the world map to detect walls.
         * \return An sf::Vector2f of the new position of Blinky.
         */
        sf::Vector2f move(const map_t & worldMap) override;

        /**
         * Returns the direction of Blinky.
         *
         * \return An int of the direction of Blinky.
         */
        int getDirection() override;

        /**
         * Returns if Blinky is collected/eaten by the player.
         *
         * \return A bool of if Blinky is collected.
         */
        bool is_collected() override;

    private:
        std::vector<std::string> blinkyDirections = {   "Blinky Back One",
                                                        "Blinky Back Two",
                                                        "Blinky Left One",
                                                        "Blinky Left Two",
                                                        "Blinky Middle One",
                                                        "Blinky Middle Two",
                                                        "Blinky Right One",
                                                        "Blinky Right Two" };
                                    
        uint direction;

        sf::Sprite blinkySprite;

        float movement_speed;
    };
}
