#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
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
         * Constructor to initialize InGamestate class.
         *
         * \param data A shared pointer to the game data.
         */
        InGameState(game_data_ref_t data);

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

    protected:
        game_data_ref_t data;
        Player player;

        /**
         * Updates the in game state outside of key presses.
         *
         * \param dt A float.
         */
        void draw(float dt);

        /**
         * Moves the character.
         *
         * \param direction A string indicating what direction the player should move.
         */
        void move(std::string direction);

    private:

        // sf::Sprite background;

        int w, h;

        // double posX, posY;
        // double dirX, dirY;
        // double planeX, planeY;
        // double moveSpeed;
        // double rotSpeed;

        sf::Clock clock;
        sf::Time fps;
    };
}
