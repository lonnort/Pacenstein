#include "Definitions.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"

#include <random>
#include <iostream>
#include <sstream>

namespace Pacenstein {
    GameOverState::GameOverState(game_data_ref_t data) : data(data) {}

    void GameOverState::parseScores(std::vector<std::string> file_content) {
        for (auto& line : file_content) {
            std::string player_name = "";
            int points = 0;

            std::stringstream ss(line);
            ss >> player_name >> points;
            player_name.pop_back();
            this->scores.push_back({player_name, points});
        }
        std::sort(scores.begin(), scores.end(), [](auto& l, auto& r){ return l.second > r.second; });
    }

    void GameOverState::saveScore(){
        std::vector<std::string> content = this->data->assets.getCsvFile("Scores");
        content.push_back(playerInput + "; " + std::to_string(this->data->score));
        this->data->assets.saveCsvFile("Scores", SCORE_FILEPATH, content);
    }

    void GameOverState::init() {
        sf::Font font = this->data->assets.getFont("Font");

        this->parseScores(this->data->assets.getCsvFile("Scores"));

        if(this->data->score == 0){
            this->data->score = 629;
        }
        
        this->position = -1;
        for (int i = 0; i < scores.size(); i++) {
            if(this->data->score > scores[i].second){
                position = i;
                break;
            }
        }
        if(position == -1){
            this->position = scores.size();
        }

        if(position <= 7){
            for(int i = 0; i < position; i++){
                positionString += std::to_string(i+1) + ".\n";
                nameStringBefore += scores[i].first + "\n";
                pointsString += std::to_string(scores[i].second) + "\n";
            }
            positionString += std::to_string(position+1) + ".\n";
            pointsString += std::to_string(this->data->score) + "\n";
            if(scores.size() < 9){
                for(int i = position; i < scores.size(); i++){
                    positionString += std::to_string(i+2) + ".\n";
                    nameStringAfter += scores[i].first + "\n";
                    pointsString += std::to_string(scores[i].second) + "\n";
                }
            }else{
                for(int i = position; i < 8; i++){
                    positionString += std::to_string(i+2) + ".\n";
                    nameStringAfter += scores[i].first + "\n";
                    pointsString += std::to_string(scores[i].second) + "\n";
                }
            }
            positionString += "...";
        }else{
            for(int i = 0; i < 3; i++){
                positionString += std::to_string(i+1) + ".\n";
                nameStringBefore += scores[i].first + "\n";
                pointsString += std::to_string(scores[i].second) + "\n";
            }
            positionString += "...\n";
            nameStringBefore += "\n";
            pointsString += "\n";
            if(position <= scores.size()-3){
                for(int i = position-2; i < position; i++){
                    positionString += std::to_string(i+1) + ".\n";
                    nameStringBefore += scores[i].first + "\n";
                    pointsString += std::to_string(scores[i].second) + "\n";
                }
                positionString += std::to_string(position+1) + ".\n";
                pointsString += std::to_string(this->data->score) + "\n";
                for(int i = position; i < position+2; i++){
                    positionString += std::to_string(i+2) + ".\n";
                    nameStringAfter += scores[i].first + "\n";
                    pointsString += std::to_string(scores[i].second) + "\n";
                }
                positionString += "...";

            }else{
                for(int i = position - (4 - (scores.size() - position)); i < position; i++){
                    positionString += std::to_string(i+1) + ".\n";
                    nameStringBefore += scores[i].first + "\n";
                    pointsString += std::to_string(scores[i].second) + "\n";
                }
                positionString += std::to_string(position+1) + ".\n";
                pointsString += std::to_string(this->data->score) + "\n";
                for(int i = position; i < scores.size(); i++){
                    positionString += std::to_string(i+2) + ".\n";
                    nameStringAfter += scores[i].first + "\n";
                    pointsString += std::to_string(scores[i].second) + "\n";
                }
            }
        }

        title.setTexture(this->data->assets.getTexture("Game Over Title"));
        backButton.setTexture(this->data->assets.getTexture("Back To Main Button"));

        title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 30);
        backButton.setPosition((SCREEN_WIDTH / 2) - (backButton.getGlobalBounds().width / 2), SCREEN_HEIGHT - 100);

        cursorHand.loadFromSystem(sf::Cursor::Hand);
        cursorArrow.loadFromSystem(sf::Cursor::Arrow);
    }

    void GameOverState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(true);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if( this->data->input.isSpriteHovered(this->backButton, this->data->window))
                this->data->window.setMouseCursor(this->cursorHand);
            else this->data->window.setMouseCursor(this->cursorArrow);

            if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window))
                this->data->machine.addState(state_ref_t(std::make_unique<MainMenuState>(this->data)), true);

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 and event.text.unicode > 32){
                    if (playerInput.size() < maxChar and !nameDone) {
                        playerInput += event.text.unicode;
                    }           
                }
            }

            if (sf::Event::KeyPressed == event.type) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::KEY_EXIT:
                        this->data->window.close();
                        break;
                    
                    case sf::Keyboard::Key::BackSpace:
                        if (playerInput != "" and !nameDone) {
                            playerInput.pop_back();
                        }
                        break;

                    case sf::Keyboard::Key::Enter:
                        if(!nameDone){
                            nameDone = true;
                            if(playerInput != ""){
                                saveScore();
                            }
                        }
                        break;
                }
            }
        }
    }

    void GameOverState::update(float dt) {
        // std::cout << "game over!" << std::endl;
    }

    void GameOverState::draw(float dt) {
        this->data->window.clear();

        std::string nameText = "";
        if(playerInput == "") {
            nameText = nameStringBefore + "<enter name>\n" + nameStringAfter;
        } else {
            nameText = nameStringBefore + playerInput + "\n" + nameStringAfter;
        }

        sf::Text scoreText("Score: " + std::to_string(this->data->score), this->data->assets.getFont("Font"));
        sf::Text leaderboardTitleText(" position   \tname\t\t  points", this->data->assets.getFont("Font"));
        sf::Text leaderboardNameText(nameText, this->data->assets.getFont("Font"));
        sf::Text leaderboardPointsText(this->pointsString, this->data->assets.getFont("Font"));
        sf::Text leaderboardPositionText(this->positionString, this->data->assets.getFont("Font"));
        leaderboardTitleText.setOrigin(leaderboardTitleText.getGlobalBounds().width / 2, leaderboardTitleText.getGlobalBounds().height / 2);
        scoreText.setPosition((SCREEN_WIDTH / 2) - (scoreText.getGlobalBounds().width / 2), 75);
        leaderboardTitleText.setPosition((SCREEN_WIDTH / 2), 150);
        leaderboardNameText.setPosition((SCREEN_WIDTH / 2) -30, 200);
        leaderboardPointsText.setPosition((SCREEN_WIDTH / 2) +160, 200);
        leaderboardPositionText.setPosition((SCREEN_WIDTH / 2) -160, 200);

        this->data->window.draw(scoreText);
        this->data->window.draw(leaderboardTitleText);
        this->data->window.draw(leaderboardPositionText);
        this->data->window.draw(leaderboardNameText);
        this->data->window.draw(leaderboardPointsText);

        this->data->window.draw(this->title);
        if(nameDone){
            sf::Text leaderboardInfo("Your score is saved!", this->data->assets.getFont("Font"));
            leaderboardInfo.setOrigin(leaderboardInfo.getGlobalBounds().width / 2, leaderboardInfo.getGlobalBounds().height / 2);
            leaderboardInfo.setPosition((SCREEN_WIDTH / 2), SCREEN_HEIGHT - 180);

            this->data->window.draw(leaderboardInfo);
            this->data->window.draw(this->backButton);
        }else{
            sf::Text leaderboardInfo("Please type your name and press enter to save!", this->data->assets.getFont("Font"));
            leaderboardInfo.setOrigin(leaderboardInfo.getGlobalBounds().width / 2, leaderboardInfo.getGlobalBounds().height / 2);
            leaderboardInfo.setPosition((SCREEN_WIDTH / 2), SCREEN_HEIGHT - 180);

            this->data->window.draw(leaderboardInfo);
        }

        this->data->window.display();
    }
}
