#include <iostream>
#include "SplashState.hpp"
#include "Definitions.hpp"
#include "MainMenuState.hpp"

namespace Pacenstein {
    SplashState::SplashState(game_data_ref_t data) : data(data) {}

    void SplashState::loadAssets() {
        // General (= dingen die in meerdere states gebruikt worden)
        this->data->assets.loadTexture("Splash Image", PACENSTEIN_LOGO_FILEPATH);
        this->data->assets.loadTexture("Back Button", (BUTTONS_FILEPATH "back.png"));
        this->data->assets.loadTexture("Leaderboard Text", (BUTTONS_FILEPATH "leaderboard.png"));
        this->data->assets.loadTexture("Settings Text", (BUTTONS_FILEPATH "settings.png"));
        this->data->assets.loadConfFile("Settings", SETTINGS_FILEPATH);
        this->data->assets.loadCsvFile("Scores", SCORE_FILEPATH);
        this->data->assets.loadFont("Font", FONT_FILEPATH);

        // In Game state
        this->data->assets.loadTexture("PacPellet",   (PELLET_FILEPATH "pac v2.png"));
        this->data->assets.loadTexture("PowerPellet", (PELLET_FILEPATH "power v2.png"));
        this->data->assets.loadTexture("Heart", (GAME_FILEPATH "heart.png"));
        this->data->assets.loadImage("Map", (MAP_FILEPATH));

        // Game over state
        this->data->assets.loadTexture("Game Over Background", BACKGROUND_FILEPATH);
        this->data->assets.loadTexture("Game Over Title",      (BUTTONS_FILEPATH "game_over.png"));
        this->data->assets.loadTexture("Score Text",           (BUTTONS_FILEPATH "score.png"));
        this->data->assets.loadTexture("Back To Main Button",  (BUTTONS_FILEPATH "to_main_menu.png"));
        this->data->assets.loadTexture("Leaderboard Position", (BUTTONS_FILEPATH "button.png"));
        this->data->assets.loadTexture("Leaderboard Name",     (BUTTONS_FILEPATH "button.png"));
        this->data->assets.loadTexture("Leaderboard Score",    (BUTTONS_FILEPATH "button.png"));

        // Credits menu
        this->data->assets.loadTexture("Credits Title", (BUTTONS_FILEPATH "credits.png"));

        // Main menu
        this->data->assets.loadTexture("Start Game Button", (BUTTONS_FILEPATH "start_game.png"));
        this->data->assets.loadTexture("Quit Game Button",  (BUTTONS_FILEPATH "quit_game.png"));
        this->data->assets.loadTexture("Credits Button",    (BUTTONS_FILEPATH "question.png"));

        // Pause menu
        this->data->assets.loadTexture("Pause Title",     (BUTTONS_FILEPATH "paused.png"));
        this->data->assets.loadTexture("Highscore Text",  (BUTTONS_FILEPATH "highscore.png"));
        this->data->assets.loadTexture("Give Up Button",  (BUTTONS_FILEPATH "give_up.png"));
        this->data->assets.loadTexture("Continue Button", (BUTTONS_FILEPATH "continue.png"));

        // Settings menu
        this->data->assets.loadTexture("Move Backward",     (BUTTONS_FILEPATH "S_key.png"));
        this->data->assets.loadTexture("Move Forward",      (BUTTONS_FILEPATH "W_key.png"));
        this->data->assets.loadTexture("Move Left",         (BUTTONS_FILEPATH "A_key.png"));
        this->data->assets.loadTexture("Move Right",        (BUTTONS_FILEPATH "D_key.png"));
        this->data->assets.loadTexture("Move Backward alt", (BUTTONS_FILEPATH "down_key.png"));
        this->data->assets.loadTexture("Move Forward alt",  (BUTTONS_FILEPATH "up_key.png"));
        this->data->assets.loadTexture("Move Left alt",     (BUTTONS_FILEPATH "left_key.png"));
        this->data->assets.loadTexture("Move Right alt",    (BUTTONS_FILEPATH "right_key.png"));
        this->data->assets.loadTexture("Pause",             (BUTTONS_FILEPATH "esc_key.png"));
        this->data->assets.loadTexture("Quit",              (BUTTONS_FILEPATH "del_key.png"));

        // Ghosts

        // Blinky
        this->data->assets.loadTexture("Blinky Back One",   (GHOSTS_FILEPATH "blinky_back_one.png"));
        this->data->assets.loadTexture("Blinky Back Two",   (GHOSTS_FILEPATH "blinky_back_two.png"));
        this->data->assets.loadTexture("Blinky Left One",   (GHOSTS_FILEPATH "blinky_left_one.png"));
        this->data->assets.loadTexture("Blinky Left Two",   (GHOSTS_FILEPATH "blinky_left_two.png"));
        this->data->assets.loadTexture("Blinky Middle One", (GHOSTS_FILEPATH "blinky_middle_one.png"));
        this->data->assets.loadTexture("Blinky Middle Two", (GHOSTS_FILEPATH "blinky_middle_two.png"));
        this->data->assets.loadTexture("Blinky Right One",  (GHOSTS_FILEPATH "blinky_right_one.png"));
        this->data->assets.loadTexture("Blinky Right Two",  (GHOSTS_FILEPATH "blinky_right_two.png"));

        // Clyde
        this->data->assets.loadTexture("Clyde Back One",    (GHOSTS_FILEPATH "clyde_back_one.png"));
        this->data->assets.loadTexture("Clyde Back Two",    (GHOSTS_FILEPATH "clyde_back_two.png"));
        this->data->assets.loadTexture("Clyde Left One",    (GHOSTS_FILEPATH "clyde_left_one.png"));
        this->data->assets.loadTexture("Clyde Left Two",    (GHOSTS_FILEPATH "clyde_left_two.png"));
        this->data->assets.loadTexture("Clyde Middle One",  (GHOSTS_FILEPATH "clyde_middle_one.png"));
        this->data->assets.loadTexture("Clyde Middle Two",  (GHOSTS_FILEPATH "clyde_middle_two.png"));
        this->data->assets.loadTexture("Clyde Right One",   (GHOSTS_FILEPATH "clyde_right_one.png"));
        this->data->assets.loadTexture("Clyde Right Two",   (GHOSTS_FILEPATH "clyde_right_two.png"));

        // Inky
        this->data->assets.loadTexture("Inky Back One",    (GHOSTS_FILEPATH "inky_back_one.png"));
        this->data->assets.loadTexture("Inky Back Two",    (GHOSTS_FILEPATH "inky_back_two.png"));
        this->data->assets.loadTexture("Inky Left One",    (GHOSTS_FILEPATH "inky_left_one.png"));
        this->data->assets.loadTexture("Inky Left Two",    (GHOSTS_FILEPATH "inky_left_two.png"));
        this->data->assets.loadTexture("Inky Middle One",  (GHOSTS_FILEPATH "inky_middle_one.png"));
        this->data->assets.loadTexture("Inky Middle Two",  (GHOSTS_FILEPATH "inky_middle_two.png"));
        this->data->assets.loadTexture("Inky Right One",   (GHOSTS_FILEPATH "inky_right_one.png"));
        this->data->assets.loadTexture("Inky Right Two",   (GHOSTS_FILEPATH "inky_right_two.png"));

        // Pinky
        this->data->assets.loadTexture("Pinky Back One",    (GHOSTS_FILEPATH "pinky_back_one.png"));
        this->data->assets.loadTexture("Pinky Back Two",    (GHOSTS_FILEPATH "pinky_back_two.png"));
        this->data->assets.loadTexture("Pinky Left One",    (GHOSTS_FILEPATH "pinky_left_one.png"));
        this->data->assets.loadTexture("Pinky Left Two",    (GHOSTS_FILEPATH "pinky_left_two.png"));
        this->data->assets.loadTexture("Pinky Middle One",  (GHOSTS_FILEPATH "pinky_middle_one.png"));
        this->data->assets.loadTexture("Pinky Middle Two",  (GHOSTS_FILEPATH "pinky_middle_two.png"));
        this->data->assets.loadTexture("Pinky Right One",   (GHOSTS_FILEPATH "pinky_right_one.png"));
        this->data->assets.loadTexture("Pinky Right Two",   (GHOSTS_FILEPATH "pinky_right_two.png"));
    }

    void SplashState::init() {
        this->loadAssets();

        this->background.setTexture(this->data->assets.getTexture("Splash Image"));
        this->background.setOrigin(this->background.getGlobalBounds().width / 2, this->background.getGlobalBounds().height / 2);
        this->background.setPosition(std::stoi(data->settings.at("window").at("Width")) / 2, std::stoi(this->data->settings.at("window").at("Height")) / 2);
        this->background.scale(.5, .5);
    }

    void SplashState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(true);

            if (sf::Event::Closed == event.type) this->data->window.close();

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
        if (this->clock.getElapsedTime().asSeconds() > 3)
            this->data->machine.addState(state_ref_t(std::make_unique<MainMenuState>(data)), true);
    }

    void SplashState::draw(float dt) {
        this->data->window.clear();
        this->data->window.draw(this->background);
        this->data->window.display();
    }
}
