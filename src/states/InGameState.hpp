#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Player.hpp"

#include "Definitions.hpp"

namespace Pacenstein {
    /**
     * The class for the in game state.
     *
     * The InGameState is used to display the current game, via raycasting.
     * It also manages the movement of the game character.
     */
    class InGameState : public State {
    public:
        /**
         * Struct containing the information needed to draw it on the screen.
         */
        struct Sprite {
            double x, y;
            sf::Texture tex;
        };

        /**
         * Constructor to initialize InGamestate class.
         *
         * \param data A shared pointer to the game data.
         */
        explicit InGameState(game_data_ref_t data);

        /**
         * Initializes the variables of the game state.
         *
         * Only called once, when the class is created.
         */
        void init();

        /**
         * Handles input from the player.
         *
         * Reacts to the AWSD and arrow keys to move the character around.
         *
         * \todo Only respond to a single click then transfer to hunting state
         */
        void handleInput();

        /**
         * Updates the in game state outside of key presses.
         *
         * \param dt A float.
         */
        void update(float dt);

        /**
         * Updates the in game state outside of key presses.
         *
         * \param dt A float.
         */
        void draw(float dt);


    protected:
        game_data_ref_t data;
        Player player;

        void move(const std::string& direction);
        void generatePauseBackground();

    private:
        int w, h;

        sf::Clock clock;
        sf::Time fps;

        std::vector<int> ZBuffer;

        sf::Texture wallTexture;
        sf::Texture doorTexture;
        sf::Texture blinkyTexture;
        sf::Texture clydeTexture;
        sf::Texture pacTexture;

        void drawWalls(map_t worldMap, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f plane);
        void drawEntities(std::vector<Sprite> sprites, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f plane);
    };
}
