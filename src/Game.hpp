#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "StateMachine.hpp"

namespace Pacenstein {
    struct GameData {
        StateMachine     machine;
        sf::RenderWindow window;
        AssetManager     assets;
        InputManager     input;
    };
    typedef std::shared_ptr<GameData> game_data_ref_t;

    class Game {
    public:
        Game(const unsigned int width, const unsigned int height, const std::string title);

    private:
        const float dt = 0.02;
        sf::Clock clock;
        game_data_ref_t data = std::make_shared<GameData>();

        void run();
    };
}
