#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the game over state.
     *
     * The game over state is activated at the end of the game, or when the player clicks the "give
     * up" button in the pause menu. The game over screen displays a snippet of the leaderboard,
     * your current score, and a button to go back to the main menu.
     */
    class GameOverState : public State {
    public:
        /**
         * The constructor for the game over state.
         *
         * \param data This is a pointer to GameData.
         */
        explicit GameOverState(game_data_ref_t data);

        /**
         * Initializes the game over state variables and screen objects.
         *
         * Should only be called once on creation of the state.
         */
        void init();

        /**
         * Handles user inputs.
         *
         * React to mouse clicks when sprites are clicked. And close the window when the X is
         * clicked.
         */
        void handleInput();

        /**
         * Updates the game over state.
         *
         * Called by the main Game loop.
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

        /**
         * Parses the previous scores from the vector with file content and saves them to the scores vector.
         *
         * \param file_content A vector with as elements the lines of the file.
         */
        void parseScores(std::vector<std::string> file_content);

    private:
		void saveScore();

        game_data_ref_t data;

        sf::Sprite title;
        sf::Sprite backButton;

        sf::Text scoreText;
        sf::Text leaderboardTitleText;
        sf::Text leaderboardPositionText;
        sf::Text leaderboardNameText;
        sf::Text leaderboardPointsText;

        sf::Cursor cursorHand;
        sf::Cursor cursorArrow;

        std::vector<std::pair<std::string, int>> scores;

        std::string positionString   = "";
        std::string nameStringBefore = "";
		std::string playerInput      = "";
		std::string nameStringAfter  = "";
        std::string pointsString     = "";

		const int maxChar = 12;
		bool nameDone = false;
        int position = 0;
    };
}
