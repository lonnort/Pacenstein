#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <vector>
#include <utility> // bevat std::pair
#include <string>

namespace Pacenstein
{
	class LeaderboardMenuState : public State
	{
	public:
		LeaderboardMenuState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		game_data_ref_t data;

		sf::Sprite background;
		//add leaderboard with highscores
		sf::Sprite title;
		sf::Sprite backButton;

		// std::vector<sf::Text> leaderboard_text;
		std::string super_long_string = "";

		std::vector<std::pair<std::string, int>> scores;

		void parseScores(std::vector<std::string> file_content);
	};

}
