#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
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
