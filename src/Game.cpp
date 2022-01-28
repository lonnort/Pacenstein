#include "Game.hpp"
#include "SplashState.hpp"
#include "GameOverState.hpp"
#include "HuntingState.hpp"
#include "InGameState.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "ScatterState.hpp"
#include "Definitions.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
    Game::Game(const std::string& title):
        data(std::make_shared<GameData>())
    {
        this->parseSettings();

        bool fullscreen;
        std::istringstream(this->data->settings.at("window").at("Fullscreen")) >> std::boolalpha >> fullscreen;

        this->data->window.create(
            sf::VideoMode(
                std::stoi(this->data->settings.at("window").at("Width")),
                std::stoi(this->data->settings.at("window").at("Height"))
            ),
            title,
            sf::Style::Default | (fullscreen ? sf::Style::Fullscreen : 0),
            sf::ContextSettings(24,8,std::stoi(this->data->settings.at("window").at("Antialiasing")))
        );

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

    void Game::parseSettings() {
        bool keybinds = false;
        bool alt_keys = false;
        bool window   = false;

        this->data->assets.loadConfFile("Settings", SETTINGS_FILEPATH);
        std::vector<std::string> file_content = this->data->assets.getConfFile("Settings");

        for (auto& line : file_content) {
            if (line[0] == ';') continue; // if line starts with ';', the whole line is a comment
            line = line.substr(0, line.find(';')); // remove everything from ';' onward if it's not the first character.

            std::string setting = "";
            std::string eq = "";
            std::string value = "";

            std::stringstream ss(line);
            ss >> setting >> eq >> value;

            if (eq == "" && value == "") {
                if (setting == "[keybindings]") {
                    keybinds = true;
                    alt_keys = false;
                    window   = false;
                }
                else if (setting == "[keybindings.alt]") {
                    keybinds = false;
                    alt_keys = true;
                    window   = false;
                }
                else if (setting == "[window]") {
                    keybinds = false;
                    alt_keys = false;
                    window   = true;
                }
            }
            else if (eq == "=" && value != "") {
                if (keybinds) {
                    if (value.size() == 1) setting = "Move " + setting;
                    this->data->settings["keybindings"][setting] = value;
                }
                else if (alt_keys) {
                    setting = "Move " + setting + " alt";
                    this->data->settings["keybindings.alt"][setting] = value;
                }
                else if (window) {
                    this->data->settings["window"][setting] = value;
                }
            }
        }
    }
}
