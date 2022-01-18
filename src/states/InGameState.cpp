#include "Definitions.hpp"
#include "InGameState.hpp"
#include "PauseState.hpp"
#include "HuntingState.hpp"
#include "ScatterState.hpp"
#include "Definitions.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <iostream>



namespace Pacenstein {
    InGameState::InGameState(game_data_ref_t data) : data(data) {}
    
    void InGameState::init() {
	this->data->assets.loadVertex("Vertex Top", sf::Vector2f(100,0),   sf::Color::Red);
	this->data->assets.loadVertex("Vertex Bottom", sf::Vector2f(100,500),  sf::Color::Blue);
	sf::Vertex vertices[4] = {
	    this->data->assets.getVertex("Vertex Top"),
	    this->data->assets.getVertex("Vertex Bottom")
	};
    }

    void InGameState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) this->data->window.close();

            /*if (this->data->input.isSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
            {
                std::cout << "Go To Game Screen" << std::endl;
            }*/

            if (sf::Event::KeyPressed == event.type) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::KEY_EXIT:
                        this->data->window.close();
                        break;

                    case sf::Keyboard::Key::KEY_PAUSE:
                    case sf::Keyboard::Key::KEY_ALT_PAUSE:
                        this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
                        break;

                    case sf::Keyboard::Key::KEY_UP:
                    case sf::Keyboard::Key::KEY_DOWN:
                    case sf::Keyboard::Key::KEY_LEFT:
                    case sf::Keyboard::Key::KEY_RIGHT:
                    case sf::Keyboard::Key::KEY_ALT_UP:
                    case sf::Keyboard::Key::KEY_ALT_DOWN:
                    case sf::Keyboard::Key::KEY_ALT_LEFT:
                    case sf::Keyboard::Key::KEY_ALT_RIGHT:
                        this->data->machine.addState(state_ref_t(std::make_unique<HuntingState>(this->data)), true);
                        break;
                }
            }
        }
    }

    void InGameState::update(float dt) {
        std::cout << "In game" << std::endl;
    }

    void InGameState::draw(float dt) {
	this->data->window.clear();
	//std::vector<sf::Vertex> vertices = {
	sf::Vertex vertices[4] = {
	    sf::Vertex(this->data->assets.getVertex("Vertex Top")),
	    sf::Vertex(this->data->assets.getVertex("Vertex Bottom"))
	};
	this->data->window.draw(vertices, 4, sf::Lines);
	this->data->window.display();
    }
}
