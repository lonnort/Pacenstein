#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <vector>
#include <utility> // bevat std::pair
#include <string>

namespace Pacenstein
{
	/**
     * The class for the leaderboard menu state.
     *
     * The LeaderboardMenuState is used to create a state that displays
	 * scores of previous players. The scores are ranked from high to low.
	 * The leaderboard menu is accessible through the main menu state.
     */
	class LeaderboardMenuState : public State
	{
	public:
		/**
		 * Constructor to initialize LeaderboardMenuState class.
		 * 
		 * \param data A shared pointer to the game data.
		 */
		LeaderboardMenuState(game_data_ref_t data);

		/**
		 * Initializes leaderboard menu variables and screen objects,
		 * and creates a leaderboard.
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
		 * Updates the leaderboard menu state
		 * 
		 * Called at a certain time interval
		 * 
		 * \param dt The maximum time to update in the game loop.
		 */
		void update(float dt);

		/**
		 * Draws the screen objects and the leaderboard on the screen.
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

		// std::vector<sf::Text> leaderboard_text;
		std::string super_long_string = "";

		std::vector<std::pair<std::string, int>> scores;

		void parseScores(std::vector<std::string> file_content);
	};

}
