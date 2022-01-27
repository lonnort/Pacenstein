#include "Game.hpp"
#include "SplashState.hpp"
#include "GameOverState.hpp"
#include "HuntingState.hpp"
#include "InGameState.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "ScatterState.hpp"

#include <iostream>

namespace Pacenstein {
    Game::Game(const std::string& title):
        data(std::make_shared<GameData>())
    {
        this->data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), title, sf::Style::Default, sf::ContextSettings(24,8,4));
        sf::Image icon_img;
        icon_img.loadFromFile("res/logo.png");
        this->data->window.setIcon(256, 256, icon_img.getPixelsPtr());
        this->data->machine.addState(state_ref_t(std::make_unique<SplashState>(this->data)));

        this->run();
    }

    void Game::run() {
        float accumulator = 0;
        float currentTime = this->clock.getElapsedTime().asSeconds();

        while (this->data->window.isOpen()) {
            float newTime, frameTime, interpolation;

            this->data->machine.processStateChanges();

            newTime = this->clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;
            if (frameTime > 0.25) frameTime = 0.25;

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= this->dt) {
                this->data->machine.getActiveState()->handleInput();
                this->data->machine.getActiveState()->update(dt);

                accumulator -= this->dt;
            }

            interpolation = accumulator / this->dt;
            this->data->machine.getActiveState()->draw(interpolation);
        }
    }
}
