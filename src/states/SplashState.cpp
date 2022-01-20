#include <iostream>
#include "SplashState.hpp"
#include "Definitions.hpp"
#include "MainMenuState.hpp"

//#define SPLASH_BACKGROUND_FILEPATH "res/splash/background.png"

namespace Pacenstein {
    SplashState::SplashState(game_data_ref_t data) : data(data) {}

    void SplashState::init() {
        // load all assets for all states
        // splash state
        this->data->assets.loadTexture("Splash Background", SPLASH_BACKGROUND_FILEPATH);
        this->background.setTexture(this->data->assets.getTexture("Splash Background"));

        // General
        this->data->assets.loadTexture("Back Button",      (BUTTONS_FILEPATH "back.png"));
        this->data->assets.loadTexture("Leaderboard Text", (BUTTONS_FILEPATH "leaderboard.png"));
        this->data->assets.loadTexture("Settings Button",  (BUTTONS_FILEPATH "settings.png"));
        this->data->assets.loadTextFile("Scores", "src/data/settings.ini");
        this->data->assets.loadFont("Font", FONT);

        // Game over state
        this->data->assets.loadTexture("Game Over Background", SPLASH_BACKGROUND_FILEPATH);
        this->data->assets.loadTexture("Game Over Title",      (BUTTONS_FILEPATH "game_over.png"));
        this->data->assets.loadTexture("Score Text",           (BUTTONS_FILEPATH "score.png"));
        this->data->assets.loadTexture("Back To Main Button",  (BUTTONS_FILEPATH "to_main_menu.png"));
        this->data->assets.loadTexture("Leaderboard Position", (BUTTONS_FILEPATH "button.png"));
        this->data->assets.loadTexture("Leaderboard Name",     (BUTTONS_FILEPATH "button.png"));
        this->data->assets.loadTexture("Leaderboard Score",    (BUTTONS_FILEPATH "button.png"));

        // Credits menu
        this->data->assets.loadTexture("Credits Title", (BUTTONS_FILEPATH "credits.png"));

        // Main menu
        this->data->assets.loadTexture("Game Title", "res/pacenstein.png");
        this->data->assets.loadTexture("Start Game Button", (BUTTONS_FILEPATH "start_game.png"));
        this->data->assets.loadTexture("Quit Game Button",  (BUTTONS_FILEPATH "quit_game.png"));
        this->data->assets.loadTexture("Credits Button",    (BUTTONS_FILEPATH "question.png"));

        // Pause menu
        this->data->assets.loadTexture("Pause Title",     (BUTTONS_FILEPATH "paused.png"));
        this->data->assets.loadTexture("Highscore Text",  (BUTTONS_FILEPATH "highscore.png"));
        this->data->assets.loadTexture("Give Up Button",  (BUTTONS_FILEPATH "give_up.png"));
        this->data->assets.loadTexture("Continue Button", (BUTTONS_FILEPATH "continue.png"));

        // Settings menu
        this->data->assets.loadTexture("Settings Title", (BUTTONS_FILEPATH "settings.png"));
        this->data->assets.loadTexture("Back Button",    (BUTTONS_FILEPATH "back.png"));

        this->data->assets.loadTexture("Move forward",      (BUTTONS_FILEPATH "W_key.png"));
        this->data->assets.loadTexture("Move backward",     (BUTTONS_FILEPATH "A_key.png"));
        this->data->assets.loadTexture("Move left",         (BUTTONS_FILEPATH "S_key.png"));
        this->data->assets.loadTexture("Move right",        (BUTTONS_FILEPATH "D_key.png"));
        this->data->assets.loadTexture("Move forward alt",  (BUTTONS_FILEPATH "up_key.png"));
        this->data->assets.loadTexture("Move backward alt", (BUTTONS_FILEPATH "down_key.png"));
        this->data->assets.loadTexture("Move left alt",     (BUTTONS_FILEPATH "left_key.png"));
        this->data->assets.loadTexture("Move right alt",    (BUTTONS_FILEPATH "right_key.png"));
        this->data->assets.loadTexture("pause",             (BUTTONS_FILEPATH "esc_key.png"));
        this->data->assets.loadTexture("Instant quit",      (BUTTONS_FILEPATH "del_key.png"));
    }

    void SplashState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type){
                this->data->window.close();
            }

            if (sf::Event::KeyPressed == event.type) {
    			switch (event.key.code) {
					case sf::Keyboard::Key::KEY_EXIT:
						this->data->window.close();
						break;
				}
			}
        }
    }

    void SplashState::update(float dt) {
        if (this->clock.getElapsedTime().asSeconds() > 1)
            this->data->machine.addState(state_ref_t(std::make_unique<MainMenuState>(data)), true);
    }

    void SplashState::draw(float dt) {
        this->data->window.clear();
        this->data->window.draw(this->background);
        this->data->window.display();
    }
}
