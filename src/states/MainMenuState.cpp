#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "InGameState.hpp"
#include "LeaderboardMenuState.hpp"
#include "SettingsMenuState.hpp"
#include "CreditsMenuState.hpp"

#include <iostream>

namespace Pacenstein {
    MainMenuState::MainMenuState(game_data_ref_t data) : data(data) {}

    void MainMenuState::init() {
        title.setTexture(this->data->assets.getTexture("Splash Image"));
        StartButton.setTexture(this->data->assets.getTexture("Start Game Button"));
        LeaderboardButton.setTexture(this->data->assets.getTexture("Leaderboard Text"));
        SettingsButton.setTexture(this->data->assets.getTexture("Settings Text"));
        QuitButton.setTexture(this->data->assets.getTexture("Quit Game Button"));
        CreditsButton.setTexture(this->data->assets.getTexture("Credits Button"));

        title.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - (title.getGlobalBounds().width / 2 * 0.3), title.getGlobalBounds().height / 2 * 0.3);
        StartButton.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - (StartButton.getGlobalBounds().width / 2), (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (StartButton.getGlobalBounds().height / 2));
        LeaderboardButton.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - (LeaderboardButton.getGlobalBounds().width / 2), (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (LeaderboardButton.getGlobalBounds().height / 2) + 75);
        SettingsButton.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - (SettingsButton.getGlobalBounds().width / 2), (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (SettingsButton.getGlobalBounds().height / 2) + 150);
        QuitButton.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - (QuitButton.getGlobalBounds().width / 2), (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (QuitButton.getGlobalBounds().height / 2) + 225);
        CreditsButton.setPosition(100, (std::stoi(this->data->settings.at("window").at("Height")) - 100) - (CreditsButton.getGlobalBounds().height));

        cursorHand.loadFromSystem(sf::Cursor::Hand);
        cursorArrow.loadFromSystem(sf::Cursor::Arrow);
    }

    void MainMenuState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(true);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if( this->data->input.isSpriteHovered(this->StartButton, this->data->window)
            ||  this->data->input.isSpriteHovered(this->LeaderboardButton, this->data->window)
            ||  this->data->input.isSpriteHovered(this->SettingsButton, this->data->window)
            ||  this->data->input.isSpriteHovered(this->QuitButton, this->data->window)
            ||  this->data->input.isSpriteHovered(this->CreditsButton, this->data->window))
            {
                this->data->window.setMouseCursor(this->cursorHand);
            }
            else this->data->window.setMouseCursor(this->cursorArrow);

            if (this->data->input.isSpriteClicked(this->StartButton, sf::Mouse::Left, this->data->window))
                this->data->machine.addState(state_ref_t(std::make_unique<InGameState>(this->data)), false);

            if (this->data->input.isSpriteClicked(this->LeaderboardButton, sf::Mouse::Left, this->data->window))
                this->data->machine.addState(state_ref_t(std::make_unique<LeaderboardMenuState>(this->data)), false);

            if (this->data->input.isSpriteClicked(this->SettingsButton, sf::Mouse::Left, this->data->window))
                this->data->machine.addState(state_ref_t(std::make_unique<SettingsMenuState>(this->data)), false);

            if (this->data->input.isSpriteClicked(this->QuitButton, sf::Mouse::Left, this->data->window))
                this->data->window.close();

            if (this->data->input.isSpriteClicked(this->CreditsButton, sf::Mouse::Left, this->data->window))
                this->data->machine.addState(state_ref_t(std::make_unique<CreditsMenuState>(this->data)), false);

            if (sf::Event::KeyPressed == event.type) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::KEY_EXIT:
                        this->data->window.close();
                        break;
                }
            }
        }
    }

    void MainMenuState::update(float dt) {
        // std::cout << "In main menu" << std::endl;
    }

    void MainMenuState::draw(float dt) {
        this->data->window.clear();
        this->title.setScale(0.3,0.3);

        this->data->window.draw(this->title);
        this->data->window.draw(this->StartButton);
        this->data->window.draw(this->LeaderboardButton);
        this->data->window.draw(this->SettingsButton);
        this->data->window.draw(this->QuitButton);
        this->data->window.draw(this->CreditsButton);

        this->data->window.display();
    }
}
