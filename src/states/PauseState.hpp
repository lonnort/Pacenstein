#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein
{
	class PauseState : public State
	{
	public:
		PauseState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
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
