#pragma once

#include "Ghost.hpp"

namespace Pacenstein {
    /**
     * The subclass for Inky.
     *
     * Inky is a subclass of Ghost, Inky is the blue ghost.
     */
    class Inky : public Ghost {
    public:
        /**
         * Constructor of the Inky ghost class.
         *
         * \param x The x position as a float of Inky.
         * \param y The y position as a float of Inky.
         */
        Inky(float x, float y, float speed = 0.05);

        /**
         * Constructor of the Inky ghost class.
         *
         * \param xy The position of Inky as a sf::Vector2f.
         */
        explicit Inky(sf::Vector2f xy, float speed = 0.05);

        /**
         * Returns the sprite of Inky based on the direction and the corresponding texture.
         *
         * \param data A reference to the game data object.
         * \return An sf::Sprite of the direction of Inky.
         */
        sf::Sprite getGhostSprite(game_data_ref_t data);

        /**
         * Moves Inky to an new position based on the direction.
         * 
         * If Inky hits a wall, the direction is randomly changed to a new one.
         *
         * \param worldMap A reference to the world map to detect walls.
         * \return An sf::Vector2f of the new position of Inky.
         */
        sf::Vector2f move(const map_t & worldMap) override;

        /**
         * Returns the direction of Inky.
         *
         * \return An int of the direction of Inky.
         */
        int getDirection() override;

        /**
         * Returns if Inky is collected/eaten by the player.
         *
         * \return A bool of if Inky is collected.
         */
        bool is_collected() override;

    private:
        std::vector<std::string> inkyDirections = {     "Inky Back One",
                                                        "Inky Back Two",
                                                        "Inky Left One",
                                                        "Inky Left Two",
                                                        "Inky Middle One",
                                                        "Inky Middle Two",
                                                        "Inky Right One",
                                                        "Inky Right Two" };
                                    
        uint direction;

        sf::Sprite inkySprite;

        float movement_speed;
    };
}
