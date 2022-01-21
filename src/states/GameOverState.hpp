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

		void parseScores(std::vector<std::string> file_content);

	private:
		game_data_ref_t data;

		sf::Sprite title;
		sf::Sprite scoreText;
		sf::Sprite leaderboardText;
		sf::Sprite leaderboardPosition;
		sf::Sprite leaderboardName;
		sf::Sprite leaderboardScore;
		sf::Sprite backButton;

		sf::Cursor cursorHand;
		sf::Cursor cursorArrow;

		std::vector<std::pair<std::string, int>> scores;
		std::string positieString = "";
		std::string naamString = "";
		std::string puntenString = "";
		int positie = 0;
	};
}
