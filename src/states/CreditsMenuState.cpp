#include "Definitions.hpp"
#include "CreditsMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Pacenstein {
    CreditsMenuState::CreditsMenuState(game_data_ref_t data) : data(data) {}

    void CreditsMenuState::init() {
        title.setTexture(this->data->assets.getTexture("Credits Title"));
        backButton.setTexture(this->data->assets.getTexture("Back Button"));

        title.setPosition((std::stoi(this->data->settings.at("window").at("Width")) / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
        backButton.setPosition((backButton.getGlobalBounds().width / 2) + 50, (backButton.getGlobalBounds().height / 2) + 50);

        cursorHand.loadFromSystem(sf::Cursor::Hand);
        cursorArrow.loadFromSystem(sf::Cursor::Arrow);
    }

    void CreditsMenuState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(true);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if (this->data->input.isSpriteHovered(this->backButton, this->data->window))
                this->data->window.setMouseCursor(this->cursorHand);
            else this->data->window.setMouseCursor(this->cursorArrow);

            if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window))
                this->data->machine.removeState();

            if (sf::Event::KeyPressed == event.type) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::KEY_EXIT:
                        this->data->window.close();
                        break;
                }
            }
        }
    }

    void CreditsMenuState::update(float dt) {}

    void CreditsMenuState::draw(float dt) {
        std::string credits = "A game made by: \n\nJarno Brocker\nLennard Duinkerken\nDaan Roth\nEmma Raijmakers";
        sf::Text creditsText(credits, this->data->assets.getFont("Font"));
        creditsText.setPosition(std::stoi(data->settings.at("window").at("Width")) / 2 - 125, 200);

        this->data->window.clear();

        this->data->window.draw(creditsText);
        this->data->window.draw(this->title);
        this->data->window.draw(this->backButton);

        this->data->window.display();
    }
}
