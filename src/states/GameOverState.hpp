#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein
{
	class GameOverState : public State
	{
	public:
		GameOverState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		game_data_ref_t data;

		sf::Sprite background;
		//add sprites for title and start button
		sf::Sprite title;
		sf::Sprite scoreText;
		sf::Sprite leaderboardText;
		sf::Sprite leaderboardPosition;
		sf::Sprite leaderboardName;
		sf::Sprite leaderboardScore;
		sf::Sprite backButton;

		sf::Cursor cursorHand;
		sf::Cursor cursorArrow;
	};
}
