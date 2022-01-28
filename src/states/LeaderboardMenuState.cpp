#include "Definitions.hpp"
#include "LeaderboardMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
    LeaderboardMenuState::LeaderboardMenuState(game_data_ref_t data) : data(data) {}

    void LeaderboardMenuState::parseScores(std::vector<std::string> file_content) {
        for (auto& line : file_content) {
            std::string player_name = "";
            int points = 0;

            std::stringstream ss(line);
            ss >> player_name >> points;
            player_name.pop_back();
            this->scores.push_back({player_name, points});
        }

        std::sort(scores.begin(), scores.end(), [](const auto& l, const auto& r){ return l.second > r.second; });

        for (uint i = 0; i < scores.size(); i++) {
            std::vector<std::string> tmp;
            tmp.push_back(std::to_string(i+1) + ".\n");
            tmp.push_back(scores[i].first + "\n");
            tmp.push_back(std::to_string(scores[i].second) + "\n");
            leaderboard.push_back(tmp);
        }
    }

    void LeaderboardMenuState::refresh_leaderboard(){
        positionString  = "";
        nameString      = "";
        pointsString    = "";
        if (this->end > this->leaderboard.size()) {
            for (uint i = 0; i < leaderboard.size(); i++) {
                positionString += leaderboard[i][0];
                nameString     += leaderboard[i][1];
                pointsString   += leaderboard[i][2];
            }
        }
        else {
            if (begin != 0) {
                positionString += "...\n";
                nameString     += "...\n";
                pointsString   += "...\n";
            }
            else {
                positionString += "\n";
                nameString     += "\n";
                pointsString   += "\n";
            }

            for (uint i = begin; i < end; i++) {
                positionString += leaderboard[i][0];
                nameString     += leaderboard[i][1];
                pointsString   += leaderboard[i][2];
            }

            if (end != leaderboard.size()) {
                positionString += "...\n";
                nameString     += "...\n";
                pointsString   += "...\n";
            }
        }
    }

    void LeaderboardMenuState::init() {
        this->parseScores(this->data->assets.getCsvFile("Scores"));

        refresh_leaderboard();

        title.setTexture(this->data->assets.getTexture("Leaderboard Text"));
        backButton.setTexture(this->data->assets.getTexture("Back Button"));

        title.setPosition(
            (std::stoi(this->data->settings.at("window").at("Width")) / 2) - (title.getGlobalBounds().width / 2),
            title.getGlobalBounds().height / 2 + 50
        );

        backButton.setPosition(
            (backButton.getGlobalBounds().width  / 2) + 50,
            (backButton.getGlobalBounds().height / 2) + 50
        );

        this->cursorHand.loadFromSystem(sf::Cursor::Hand);
        this->cursorArrow.loadFromSystem(sf::Cursor::Arrow);
    }

    void LeaderboardMenuState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(true);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if(this->data->input.isSpriteHovered(this->backButton, this->data->window))
                this->data->window.setMouseCursor(this->cursorHand);
            else this->data->window.setMouseCursor(this->cursorArrow);

            if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window))
                this->data->machine.removeState();

            if (sf::Event::KeyPressed == event.type) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::KEY_EXIT: {
                        this->data->window.close();
                        break;
                    }

                    case sf::Keyboard::Down: {
                        if (end < leaderboard.size()) {
                            begin++;
                            end++;
                            refresh_leaderboard();
                        }
                        break;
                    }

                    case sf::Keyboard::Up: {
                        if (begin > 0) {
                            begin--;
                            end--;
                            refresh_leaderboard();
                        }
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta < 0) {
                    if (end < leaderboard.size()) {
                        begin++;
                        end++;
                    }
                }
                else {
                    if(begin > 0) {
                        begin--;
                        end--;
                    }
                }
                refresh_leaderboard();
            }
        }
    }

    void LeaderboardMenuState::update(float dt) {}

    void LeaderboardMenuState::draw(float dt) {
        this->data->window.clear();

        sf::Text leaderboardTitleText(" position   \tname\t\t  points", this->data->assets.getFont("Font"));
        sf::Text leaderboardNameText    (this->nameString,     this->data->assets.getFont("Font"));
        sf::Text leaderboardPointsText  (this->pointsString,   this->data->assets.getFont("Font"));
        sf::Text leaderboardPositionText(this->positionString, this->data->assets.getFont("Font"));

        leaderboardTitleText.setOrigin(
            leaderboardTitleText.getGlobalBounds().width  / 2,
            leaderboardTitleText.getGlobalBounds().height / 2
        );

        leaderboardTitleText.setPosition   ((std::stoi(data->settings.at("window").at("Width")) / 2),       150);
        leaderboardNameText.setPosition    ((std::stoi(data->settings.at("window").at("Width")) / 2) -  30, 200);
        leaderboardPointsText.setPosition  ((std::stoi(data->settings.at("window").at("Width")) / 2) + 160, 200);
        leaderboardPositionText.setPosition((std::stoi(data->settings.at("window").at("Width")) / 2) - 160, 200);

        this->data->window.draw(leaderboardTitleText);
        this->data->window.draw(leaderboardPositionText);
        this->data->window.draw(leaderboardNameText);
        this->data->window.draw(leaderboardPointsText);

        this->data->window.draw(this->title);
        this->data->window.draw(this->backButton);

        this->data->window.display();
    }
}
