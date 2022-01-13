#include "Game.hpp"
#include "SplashState.hpp"
#include "iostream"

namespace Pacenstein {
    Game::Game(const unsigned int width, const unsigned int height, const std::string title) {
        this->data->window.create(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24,8,8));
        this->data->machine.addState(state_ref_t(std::make_unique<SplashState>(this->data)));

        this->run();
    }

    void Game::run() {
        float newTime       = 0;
        float frameTime     = 0;
        float interpolation = 0;
        float accumulator   = 0;
        float currentTime   = this->clock.getElapsedTime().asSeconds();

        while (this->data->window.isOpen()) {
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