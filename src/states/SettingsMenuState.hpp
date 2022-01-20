#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein
{
	class SettingsMenuState : public State
	{
	public:
		SettingsMenuState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
		void parseSettings(std::vector<std::string> file_content);

	private:
		game_data_ref_t data;

		sf::Sprite background;
		sf::Sprite title;
		sf::Sprite backButton;

		sf::Cursor cursorHand;
		sf::Cursor cursorArrow;

		std::vector<sf::Sprite> sprites;

		std::vector<std::vector<std::string>> settings;
		std::string super_long_string = "";
	};
}
