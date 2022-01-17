#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein
{
	class HuntingState : public State
	{
	public:
		HuntingState(game_data_ref_t data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		game_data_ref_t data;

		sf::Sprite background;
		//add sprites for title and start button
		//sf::Sprite title;
		//sf::Sprite playButton;
	};
}
