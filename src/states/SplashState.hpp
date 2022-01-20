#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
    class SplashState : public State {
    public:
        SplashState(game_data_ref_t data);

        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);

    private:
        game_data_ref_t data;
        sf::Clock clock;
        sf::Sprite  background;

        void loadAssets();
    };
}
