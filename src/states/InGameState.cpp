#include "Definitions.hpp"
#include "InGameState.hpp"
#include "PauseState.hpp"
#include "HuntingState.hpp"
#include "ScatterState.hpp"
#include "Definitions.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <iostream>
#include <cmath>

namespace Pacenstein {
    InGameState::InGameState(game_data_ref_t data) : 
        data(data),
        player()
    {}
    
    void InGameState::init() {
        this->w = SCREEN_WIDTH;
        this->h = SCREEN_HEIGHT;

        player.resetLives();
        player.resetScore();
    }

    void InGameState::generatePauseBackground() {
        sf::Texture background_img;
        background_img.create(this->data->window.getSize().x, this->data->window.getSize().y);
        background_img.update(this->data->window);
        this->data->assets.loadTexture("Pause Background", background_img);
    }

    void InGameState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(false);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_UP)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_UP)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_DOWN)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_DOWN)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_RIGHT)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_RIGHT)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_LEFT)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_LEFT)) {
                this->data->machine.addState(state_ref_t(std::make_unique<HuntingState>(this->data)), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_PAUSE)
            ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_PAUSE)) {
                this->generatePauseBackground();
                this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_EXIT)) {
                this->data->window.close();
            }
        }
    }

    void InGameState::update(float dt) {
        /** \todo Onderstaande code naar hunting state verplaatsen */

        // pseudo code voor punten optellen enzo

        // if (intersects(player, item)) {           // misschien iets met global bounds doen en de intersect functie van sfml
        //     player.addToScore(item.getPoints());  // deze kan letterlijk gecopieerd worden
        //     item.removeFromMap();                 // nodig omdat anders het item achter blijft

        //     if (item == powerPellet) goto scatterState;
        // }
    }

    void InGameState::move(std::string direction) {
        const auto worldMap = this->data->assets.getImage("Map");

        if (direction == "left")  player.moveLeft();
        if (direction == "right") player.moveRight();
        if (direction == "up")    player.moveUp(worldMap);
        if (direction == "down")  player.moveDown(worldMap);
    }

    void InGameState::draw(float dt) {
        this->data->window.clear();

        const auto worldMap = this->data->assets.getImage("Map");

        for(int x = 0; x < w; x++) {
            // calculate ray position and direction
            double cameraX = 2 * x / double(w) - 1; // x-coordinate in camera space
            double rayPosX = player.getPosX();
            double rayPosY = player.getPosY();
            double rayDirX = player.getDirX() + player.getPlaneX() * cameraX;
            double rayDirY = player.getDirY() + player.getPlaneY() * cameraX;

            // which box of the map we're in
            int mapX = int(rayPosX);
            int mapY = int(rayPosY);

            // length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            // length of ray from one x or y-side to next x or y-side
            double deltaDistX = std::sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
            double deltaDistY = std::sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
            double perpWallDist;

            // what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; // was there a wall hit?
            int side;    // was a NS or a EW wall hit?

            //calculate step and initial sideDist
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (rayPosX - mapX) * deltaDistX;
            }
            else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
            }

            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (rayPosY - mapY) * deltaDistY;
            }
            else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
            }

            // perform DDA
            while (hit == 0) {
                // jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                // Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }

            // Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
            if (side == 0) perpWallDist = std::fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
            else           perpWallDist = std::fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

            //Calculate height of line to draw on screen
            int lineHeight = std::abs(int(h / perpWallDist));

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + h / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + h / 2;
            if (drawEnd >= h) drawEnd = h - 1;

            //choose wall color
            sf::Color color;
            switch(worldMap[mapX][mapY]) {
                case 1:  color = sf::Color::Red;    break;
                case 2:  color = sf::Color::Green;  break;
                case 3:  color = sf::Color::Blue;   break;
                case 4:  color = sf::Color::White;  break;
                default: color = sf::Color::Yellow; break;
            }

            //give x and y sides different brightness
            if (side == 1) color = sf::Color(color.r/2, color.g/2, color.b/2);

            //draw the pixels of the stripe as a vertical line
            sf::Vertex line[2] = {
                sf::Vertex(sf::Vector2f(x, drawStart), color),
                sf::Vertex(sf::Vector2f(x, drawEnd), color)
            };
            this->data->window.draw(line , 2, sf::Lines);
        } // end for-loop

        this->fps = this->clock.getElapsedTime();
        float fpsValue = 1e6/fps.asMicroseconds();
        this->clock.restart();

        player.setMoveSpeed(fps.asSeconds() * 150.0); //the constant value is in squares/second
        player.setRotSpeed (fps.asSeconds() * 150.0); //the constant value is in radians/second

        sf::Text scoreText("Score: " + std::to_string(player.getScore()), this->data->assets.getFont("Font"));
        scoreText.setPosition(5, 5);
        this->data->window.draw(scoreText);

        sf::Text livesText("Lives: ", this->data->assets.getFont("Font"));
        livesText.setPosition(5, SCREEN_HEIGHT - livesText.getGlobalBounds().height - 25);
        this->data->window.draw(livesText);

        for(unsigned int i = 0; i < player.getLives(); i++){
            sf::Sprite heart;
            heart.setTexture(this->data->assets.getTexture("Heart"));
            heart.setPosition(livesText.getGlobalBounds().width + ((10 + heart.getGlobalBounds().width) * i ), SCREEN_HEIGHT - heart.getGlobalBounds().height - 5);
            this->data->window.draw(heart);
        }

        this->data->window.display();
    }
}
