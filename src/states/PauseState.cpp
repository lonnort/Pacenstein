#include "Definitions.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "SettingsMenuState.hpp"

#include <iostream>
#include <SFML/Graphics/Shader.hpp>

namespace Pacenstein {
    PauseState::PauseState(game_data_ref_t data) : data(data) {}

    void PauseState::init() {

        this->background.setTexture    (this->data->assets.getTexture("Pause Background"));
        this->title.setTexture         (this->data->assets.getTexture("Pause Title"));
        this->highscoreText.setTexture (this->data->assets.getTexture("Highscore Text"));
        this->giveUpButton.setTexture  (this->data->assets.getTexture("Give Up Button"));
        this->continueButton.setTexture(this->data->assets.getTexture("Continue Button"));
        this->settingsButton.setTexture(this->data->assets.getTexture("Settings Text"));

        this->title.setPosition(
            (std::stoi(data->settings.at("window").at("Width")) / 2) - (this->title.getGlobalBounds().width / 2),
            this->title.getGlobalBounds().height / 2
        );
        this->highscoreText.setPosition(
            (std::stoi(data->settings.at("window").at("Width")) / 2) - (this->highscoreText.getGlobalBounds().width / 2),
            (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (this->highscoreText.getGlobalBounds().height / 2) - 200
        );
        this->continueButton.setPosition(
            (std::stoi(data->settings.at("window").at("Width")) / 2) - (this->continueButton.getGlobalBounds().width / 2),
            105 + (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (this->continueButton.getGlobalBounds().height / 2) + 2 * (this->continueButton.getGlobalBounds().height)
        );
        this->giveUpButton.setPosition(
            (std::stoi(data->settings.at("window").at("Width")) / 2) - (this->giveUpButton.getGlobalBounds().width / 2) - 200,
            100 + (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (this->continueButton.getGlobalBounds().height / 2) + 2 * (this->continueButton.getGlobalBounds().height)
        );
        this->settingsButton.setPosition(
            (std::stoi(data->settings.at("window").at("Width")) / 2) - (this->settingsButton.getGlobalBounds().width / 2) + 200,
            100 + (std::stoi(this->data->settings.at("window").at("Height")) / 2) - (this->settingsButton.getGlobalBounds().height / 2) + 2 * (this->settingsButton.getGlobalBounds().height)
        );

        this->cursorHand.loadFromSystem(sf::Cursor::Hand);
        this->cursorArrow.loadFromSystem(sf::Cursor::Arrow);
    }

    void PauseState::handleInput(){
        sf::Event event;

        while (this->data->window.pollEvent(event)){
            this->data->window.setMouseCursorVisible(true);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if(this->data->input.isSpriteHovered(this->giveUpButton, this->data->window)
            || this->data->input.isSpriteHovered(this->continueButton, this->data->window)
            || this->data->input.isSpriteHovered(this->settingsButton, this->data->window))
            {
                this->data->window.setMouseCursor(this->cursorHand);
            }
            else this->data->window.setMouseCursor(this->cursorArrow);

            if (this->data->input.isSpriteClicked(this->continueButton, sf::Mouse::Left, this->data->window)) {
                // std::cout << "Continue game" << std::endl;
                this->data->machine.removeState();
            }

            if (this->data->input.isSpriteClicked(this->giveUpButton, sf::Mouse::Left, this->data->window)){
                // std::cout << "Go To Game Over Screen" << std::endl;
                this->data->machine.addState(state_ref_t(std::make_unique<GameOverState>(this->data)), true);
            }

            if (this->data->input.isSpriteClicked(this->settingsButton, sf::Mouse::Left, this->data->window)){
                // std::cout << "Go To Settings Screen" << std::endl;
                this->data->machine.addState(state_ref_t(std::make_unique<SettingsMenuState>(this->data)), false);
            }

            if (sf::Event::KeyPressed == event.type) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::KEY_EXIT:
                        this->data->window.close();
                        break;

                    case sf::Keyboard::Key::KEY_PAUSE:
                    case sf::Keyboard::Key::KEY_ALT_PAUSE:
                        this->data->machine.removeState();
                        break;
                }
            }
        }
    }

    void PauseState::update(float dt){
        // std::cout << "Pause" << std::endl;
    }

    void PauseState::draw(float dt){
        this->data->window.clear();
        if (!sf::Shader::isAvailable()) {
            sf::Shader gauss;
            if (gauss.loadFromFile("GaussianBlur.frag", sf::Shader::Fragment))
                this->data->window.draw(this->background, &gauss);
        }
        else this->data->window.draw(this->background);

        this->data->window.draw(this->title);
        this->data->window.draw(this->highscoreText);
        this->data->window.draw(this->giveUpButton);
        this->data->window.draw(this->continueButton);
        this->data->window.draw(this->settingsButton);

        this->data->window.display();
    }
}
