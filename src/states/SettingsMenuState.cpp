#include "Definitions.hpp"
#include "SettingsMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
    SettingsMenuState::SettingsMenuState(game_data_ref_t data) : data(data) {}

    void SettingsMenuState::init() {
        this->cursorHand.loadFromSystem(sf::Cursor::Hand);
        this->cursorArrow.loadFromSystem(sf::Cursor::Arrow);

        int offset = 0;
        for (auto& setting : this->data->settings.at("keybindings")) {
            sf::Sprite tmp;
            tmp.setTexture(this->data->assets.getTexture(setting.first));
            tmp.setPosition(std::stoi(data->settings.at("window").at("Width")) / 2 + 20, 200 + offset);
            this->sprites.push_back(tmp);
            offset += 60;

            this->super_long_string += setting.first;
            if (setting != *(this->data->settings.at("keybindings").end())) super_long_string += "\n\n";
        }

        offset = 0;
        for (auto& setting : this->data->settings.at("keybindings.alt")) {
            sf::Sprite tmp;
            tmp.setTexture(this->data->assets.getTexture(setting.first));
            tmp.setPosition(std::stoi(data->settings.at("window").at("Width")) / 2 + 100, 200 + offset);
            this->sprites.push_back(tmp);
            offset += 60;
        }

        title.setTexture(this->data->assets.getTexture("Settings Text"));
        backButton.setTexture(this->data->assets.getTexture("Back Button"));

        title.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
        backButton.setPosition((backButton.getGlobalBounds().width / 2) + 50, (backButton.getGlobalBounds().height / 2) + 50);
    }

    void SettingsMenuState::handleInput(){
        sf::Event event;

        while (this->data->window.pollEvent(event)){
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

    void SettingsMenuState::update(float dt) {}

    void SettingsMenuState::draw(float dt) {
        this->data->window.clear();

        this->data->window.draw(this->title);
        this->data->window.draw(this->backButton);

        for(auto sp : this->sprites) this->data->window.draw(sp);

        sf::Text text(this->super_long_string, this->data->assets.getFont("Font"));
        text.setPosition(std::stoi(data->settings.at("window").at("Width")) / 2 -200, 190);
        this->data->window.draw(text);

        this->data->window.display();
    }
}
