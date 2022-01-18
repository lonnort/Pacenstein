#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
	class CreditsMenuState : public State {
	public:
		CreditsMenuState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		game_data_ref_t data;

		sf::Sprite background;

		sf::Sprite title;
		sf::Sprite backButton;
	};
}

