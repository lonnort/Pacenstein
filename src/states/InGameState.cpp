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
    InGameState::InGameState(game_data_ref_t data) : data(data) {}
    
    void InGameState::init() {
        this->w = SCREEN_WIDTH;
        this->h = SCREEN_HEIGHT;

        // this->posX = 2;
        // this->posY = 2;
        // this->dirX = -1;
        // this->dirY = 0;
        // this->planeX = 0;
        // this->planeY = 0.66;
    }

    void InGameState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(false);

        if (sf::Event::Closed == event.type) this->data->window.close();

        if (sf::Event::KeyPressed == event.type) {
            switch (event.key.code) {
                case sf::Keyboard::Key::KEY_EXIT:
                    this->data->window.close();
                    break;

                case sf::Keyboard::Key::KEY_PAUSE:
                case sf::Keyboard::Key::KEY_ALT_PAUSE:
                    this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
                    break;

                case sf::Keyboard::Key::KEY_UP:
                case sf::Keyboard::Key::KEY_ALT_UP:
                    move("up");
                    break;
                case sf::Keyboard::Key::KEY_DOWN:
                case sf::Keyboard::Key::KEY_ALT_DOWN:
                    move("down");
                    break;
                case sf::Keyboard::Key::KEY_LEFT:
                case sf::Keyboard::Key::KEY_ALT_LEFT:
                    move("left");
                    break;
                case sf::Keyboard::Key::KEY_RIGHT:
                case sf::Keyboard::Key::KEY_ALT_RIGHT:
                    move("right");
                    break;
                }
            }
        }
    }

    void InGameState::update(float dt) {}

    void InGameState::move(std::string direction) {
        int worldMap[21][19] {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
            {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
            {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
            {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
            {1,1,1,1,0,1,0,1,1,2,1,1,0,1,0,1,1,1,1},
            {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
            {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
            {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
            {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
            {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
            {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
            {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };


        if (direction == "left") {
            player.moveLeft();
            // double oldDirX = this->dirX;
            // this->dirX = this->dirX * cos(this->rotSpeed) - this->dirY * sin(this->rotSpeed);
            // this->dirY = oldDirX * sin(this->rotSpeed) + this->dirY * cos(this->rotSpeed);
            // double oldPlaneX = this->planeX;
            // this->planeX = this->planeX * cos(this->rotSpeed) - this->planeY * sin(this->rotSpeed);
            // this->planeY = oldPlaneX * sin(this->rotSpeed) + this->planeY * cos(this->rotSpeed);
        }
        else if (direction == "right") {
            player.moveRight();
            // double oldDirX = dirX;
            // this->dirX = this->dirX * cos(-this->rotSpeed) - this->dirY * sin(-this->rotSpeed);
            // this->dirY = oldDirX * sin(-this->rotSpeed) + this->dirY * cos(-this->rotSpeed);
            // double oldPlaneX = planeX;
            // this->planeX = this->planeX * cos(-this->rotSpeed) - this->planeY * sin(-this->rotSpeed);
            // this->planeY = oldPlaneX * sin(-this->rotSpeed) + this->planeY * cos(-this->rotSpeed);
        }
        else if (direction == "up") {
            player.moveUp(worldMap);
            // if(worldMap[int(posX + this->dirX * this->moveSpeed)][int(posY)] == false) posX += this->dirX * this->moveSpeed;
            // if(worldMap[int(posX)][int(posY + this->dirY * this->moveSpeed)] == false) posY += this->dirY * this->moveSpeed;
        }
        else if (direction == "down") {
            player.moveDown(worldMap);
            // if(worldMap[int(posX - this->dirX * this->moveSpeed)][int(posY)] == false) posX -= this->dirX * this->moveSpeed;
            // if(worldMap[int(posX)][int(posY - this->dirY * this->moveSpeed)] == false) posY -= this->dirY * this->moveSpeed;
        }
    }

    void InGameState::draw(float dt) {
        this->data->window.clear();

        int worldMap[21][19] {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
            {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
            {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
            {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
            {1,1,1,1,0,1,0,1,1,2,1,1,0,1,0,1,1,1,1},
            {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
            {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
            {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
            {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
            {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
            {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
            {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

        for(int x = 0; x < w; x++) {
            //calculate ray position and direction
            double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
            double rayPosX = player.getPosX();
            double rayPosY = player.getPosY();
            double rayDirX = player.getDirX() + player.getPlaneX() * cameraX;
            double rayDirY = player.getDirY() + player.getPlaneY() * cameraX;

            //which box of the map we're in
            int mapX = int(rayPosX);
            int mapY = int(rayPosY);

            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            //length of ray from one x or y-side to next x or y-side
            double deltaDistX = std::sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
            double deltaDistY = std::sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
            double perpWallDist;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

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

            //perform DDA
            while (hit == 0) {
                //jump to next map square, OR in x-direction, OR in y-direction
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
                //Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }

            //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
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
        player.setRotSpeed(fps.asSeconds() * 60.0);  //the constant value is in radians/second

        this->data->window.display();
        this->data->window.clear();
    }
}
