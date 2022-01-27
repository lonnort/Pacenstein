#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the main menu state.
     *
     * The MainMenuState is used to create a state that displays
     * options for a player to choose from, before starting the game.
     * These options are: start game, leaderboard, settings, quit game and credits.
     */
    class MainMenuState : public State {
    public:
        /**
         * Constructor to initialize MainMenuState class.
         *
         * \param data A shared pointer to the game data.
         */
        explicit MainMenuState(game_data_ref_t data);

        /**
         * Initializes main menu variables and screen objects,
         * and creates options.
         *
         * Only called once, when the class object is created.
         */
        void init();

        /**
         * Handles input from player.
         *
         * Reacts to mouse input when a sprite is clicked,
         * when a sprite is hovered over and when the window is closed.
         */
        void handleInput();

        /**
         * Updates the main menu state.
         *
         * Called at a certain time interval.
         *
         * \param dt The maximum time to update in the game loop.
         */
        void update(float dt);

        /**
         * Draws the screen objects and the options on the screen.
         *
         * \param dt The maximum time to draw in the game loop.
         */
        void draw(float dt);

    private:
        game_data_ref_t data;

        sf::Sprite title;
        sf::Sprite StartButton;
        sf::Sprite LeaderboardButton;
        sf::Sprite SettingsButton;
        sf::Sprite QuitButton;
        sf::Sprite CreditsButton;

        sf::Cursor cursorHand;
        sf::Cursor cursorArrow;
    };
}
