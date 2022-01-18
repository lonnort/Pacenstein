#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
    class InGameState : public State {
    public:
	InGameState(game_data_ref_t data);
	
	void init();
	
	void handleInput();
	void update(float dt);
	void draw(float dt);

    private:
	game_data_ref_t data;
	
	sf::Sprite background;
	sf::Vertex lines[2];
	sf::Vertex vertices[4];
	//add sprites for title and start button
	//sf::Sprite title;
	//sf::Sprite playButton;
    };
}
