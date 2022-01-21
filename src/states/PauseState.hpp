#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein
{
	/**
     * The class for the pause menu state.
     *
     * The PauseMenuState is used to create a state in which
	 * a player can take a break from the game and display 
	 * options for when the game is paused. These options are:
	 * give up, continue and settings.
     */
	class PauseState : public State
	{
	public:
		/**
		 * Constructor to initialize PauseState class.
		 * 
		 * \param data A shared pointer to the game data.
		 */
		PauseState(game_data_ref_t data);

		/**
		 * Initializes pause state variables and screen objects.
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
		 * Updates the pause state.
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
		void draw(float dt);

	private:
		game_data_ref_t data;

		sf::Sprite background;

		sf::Sprite title;
		sf::Sprite highscoreText;
		sf::Sprite giveUpButton;
		sf::Sprite continueButton;
		sf::Sprite settingsButton;

		sf::Cursor cursorHand;
		sf::Cursor cursorArrow;
	};
}
