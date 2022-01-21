#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "State.hpp"
#include "Game.hpp"

#include "Definitions.hpp"

namespace Pacenstein {
    class InGameState : public State {
    public:
		InGameState(game_data_ref_t data);
		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);
	
		void move(std::string direction);

    private:
		game_data_ref_t data;
	
		sf::Sprite background;
	
	        int w, h;
	        double posX, posY;
	        double dirX, dirY;
	        double planeX, planeY;
	        double moveSpeed;
	        double rotSpeed;
	        sf::Clock clock;
	        sf::Time fps;
    };
}
