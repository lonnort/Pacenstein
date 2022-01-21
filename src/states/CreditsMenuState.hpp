#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the credits menu state.
     *
     * The CreditsMenuState is used to create a state that displays
     * information about the creators of the game and shows which
     * creator is responsible for a functionalty of the game.
     * The credits menu is accessible through the main menu state.
     */
    class CreditsMenuState : public State {
    public:
        /**
         * Constructor to initialize CreditsMenuState class.
         *
         * \param data A shared pointer to the game data.
         */
        CreditsMenuState(game_data_ref_t data);

        /**
         * Initializes credit menu variables and screen objects.
         *
         * Only called once, when the class object is created.
         */
        void init();

        /**
         * Handles input from player.
         *
         * Reacts to mouse input when a sprite is clicked,
         * when a sprite is hovered over, and when the window is closed.
         */
        void handleInput();

        /**
         * Updates the credit menu state.
         *
         * Called at a certain time interval
         *
         * \param dt The maximum time to update in the game loop.
         */
        void update(float dt);

        /**
         * Draws the screen objects on the screen.
         *
         * \param dt The maximum time to draw in the game loop.
         */
        void draw(float dt);

    private:
        game_data_ref_t data;

        sf::Sprite background;
        sf::Sprite title;
        sf::Sprite backButton;

        sf::Cursor cursorHand;
        sf::Cursor cursorArrow;
    };
}

