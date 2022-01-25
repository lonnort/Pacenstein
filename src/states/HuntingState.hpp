#pragma once

#include <SFML/Graphics.hpp>
#include "InGameState.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the hunting state.
     *
     * The HuntingState is used to create a state in which
     * specific entities change their behavior. 
     */
    class HuntingState : public InGameState {
    public:
        /**
         * Constructor to initialize HuntingState class.
         *
         * \param data A shared pointer to the game data.
         */
        HuntingState(game_data_ref_t data);

        /**
         * Initializes the hunting state variables.
         *
         * Only called once, when the class object is created.
         */
        // void init();

        /**
         * Handles input from the player.
         *
         * Reacts to the AWSD and arrow keys to move the character around.
         */
        void handleInput();

        /**
         * Updates the hunting state.
         *
         * Called at a certain time interval.
         *
         * \param dt The maximum time to update in the game loop.
         */
        void update(float dt);

        /**
         * Draws the screen objects on the screen.
         *
         * \param dt The maximum time to draw in the game loop.
         */
        // void draw(float dt);

    private:
        game_data_ref_t data;

        const bool huntingState = true;

        // sf::Sprite background;
    };
}
