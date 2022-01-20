#include "Definitions.hpp"
#include "InGameState.hpp"
#include "PauseState.hpp"
#include "HuntingState.hpp"
#include "ScatterState.hpp"
#include "Definitions.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <iostream>
#include <math.h>

namespace Pacenstein {
    InGameState::InGameState(game_data_ref_t data) : data(data) {}
    
    void InGameState::init() {
		this->posX = 4;
		this->posY = 4;

		this->dirX = -1;
		this->dirY = 0;

		this->planeX = 0, this->planeY = 0.66;
		this->oldPlaneX = 0; this->oldPlaneY = 0.66;
		this->time = 0, this->oldTime = 0;
	
		int worldMap[21][19]= {
		    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		    {1,4,4,4,4,4,4,4,4,1,4,4,4,4,4,4,4,4,1},
		    {1,3,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,3,1},
		    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
		    {1,4,1,1,4,1,4,1,1,1,1,1,4,1,4,1,1,4,1},
		    {1,4,4,4,4,1,4,4,4,1,4,4,4,1,4,4,4,4,1},
		    {1,1,1,1,4,1,1,1,0,1,0,1,1,1,4,1,1,1,1},
		    {0,0,0,1,4,1,0,0,0,0,0,0,0,1,4,1,0,0,0},
		    {1,1,1,1,4,1,0,1,1,2,1,1,0,1,4,1,1,1,1},
		    {0,0,0,1,4,0,0,1,0,0,0,1,0,0,4,1,0,0,0},
		    {1,1,1,1,4,1,0,1,1,1,1,1,0,1,4,1,1,1,1},
		    {0,0,0,1,4,1,0,0,0,0,0,0,0,1,4,1,0,0,0},
		    {1,1,1,1,4,1,0,1,1,1,1,1,0,1,4,1,1,1,1},
		    {1,4,4,4,4,4,4,4,4,1,4,4,4,4,4,4,4,4,1},
		    {1,4,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,4,1},
		    {1,3,4,1,4,4,4,4,4,4,4,4,4,4,4,1,4,3,1},
		    {1,1,4,1,4,1,4,1,1,1,1,1,4,1,4,1,4,1,1},
		    {1,4,4,4,4,1,4,4,4,1,4,4,4,1,4,4,4,4,1},
		    {1,4,1,1,1,1,1,1,4,1,4,1,1,1,1,1,1,4,1},
		    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
		    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
    }
    
    void InGameState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(false);
			
			if (sf::Event::Closed == event.type) this->data->window.close();

            /*if (this->data->input.isSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
            {
                std::cout << "Go To Game Screen" << std::endl;
            }*/

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
                        // this->data->machine.addState(state_ref_t(std::make_unique<HuntingState>(this->data)), true);
                }
            }
        }
    }

    void InGameState::move(std::string direction) {
		if (direction == "left") {
	            //both camera direction and camera plane must be rotated
	            double oldDirX = this->dirX;
	            this->dirX = this->dirX * cos(rotSpeed) - this->dirY * sin(rotSpeed);
	            this->dirY = oldDirX * sin(rotSpeed) + this->dirY * cos(rotSpeed);
	            double oldPlaneX = this->planeX;
	            this->planeX = this->planeX * cos(rotSpeed) - this->planeY * sin(rotSpeed);
	            this->planeY = oldPlaneX * sin(rotSpeed) + this->planeY * cos(rotSpeed);
		}
		else if (direction == "right") {
	            double oldDirX = dirX;
	            this->dirX = this->dirX * cos(-rotSpeed) - this->dirY * sin(-rotSpeed);
	            this->dirY = oldDirX * sin(-rotSpeed) + this->dirY * cos(-rotSpeed);
	            double oldPlaneX = planeX;
	            this->planeX = this->planeX * cos(-rotSpeed) - this->planeY * sin(-rotSpeed);
	            this->planeY = this->oldPlaneX * sin(-rotSpeed) + this->planeY * cos(-rotSpeed);

		}
		else if (direction == "up") {
		    if(this->worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		    if(this->worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
		}
		else if (direction == "down") {
		    if(this->worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		    if(this->worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		}
		std::cout << planeX << '\n';
    }

    void InGameState::update(float dt) {
        //std::cout << "In game" << std::endl;
		std::cout << "posX: " << this->posX << " posY: " << this->posY << '\n';
		std::cout << "dirX: " << this->dirX << " dirY: " << this->dirY << '\n';
		std::cout << "planeX: " << this->planeX << " planeY: " << this->planeY << '\n';
		std::cout << "camera: "<< this->cameraX << '\n';

		std::cout << std::endl;
    }

    // Check https://lodev.org/cgtutor/raycasting.html for the original algoritm to generate a 2.5D world.
    // This is a port of that specific algoritm for SFML.
    void InGameState::draw(float dt) {
		this->data->window.clear();
		//std::vector<sf::Vertex> vertices = {
		// loop door de hele breedte van het scherm

		this->data->window.setFramerateLimit(60);
		sf::Clock clock = sf::Clock();
		sf::Time fps;

		for (int x = 0; x < SCREEN_WIDTH; x++) {
		    //calculate ray position and direction
		    this->cameraX = 2 * x / double(SCREEN_WIDTH) - 1; //x-coordinate in camera space
		    double rayDirX = this->dirX + this->planeX * this->cameraX;
		    double rayDirY = this->dirY + this->planeY * this->cameraX;

		    //which box of the map we're in
		    int mapX = int(this->posX);
		    int mapY = int(this->posY);

		    //length of ray from current position to next x or y-side
		    double sideDistX;
		    double sideDistY;

		    //length of ray from one x or y-side to next x or y-side
		    double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		    double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		    double perpWallDist;

		    //what direction to step in x or y-direction (either +1 or -1)
		    int stepX;
		    int stepY;

		    int hit = 0; //was there a wall hit?
		    int side; //was a NS or a EW wall hit?

		    //calculate step and initial sideDist
		    if (rayDirX < 0) {
				stepX = -1;
				sideDistX = (this->posX - mapX) * deltaDistX;
		    }
		    else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - this->posX) * deltaDistX;
		    }

		    if (rayDirY < 0) {
				stepY = -1;
				sideDistY = (this->posY - mapY) * deltaDistY;
		    }
		    else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - this->posY) * deltaDistY;
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
				if (this->worldMap[mapX][mapY] > 0) {
				    hit = 1;
				}
		    }

		    //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		    if (side == 0) {
				perpWallDist = fabs((mapX - this->posX + (1 - stepX) / 2) / rayDirX);
		    }
		    else {
				perpWallDist = fabs((mapY - this->posY + (1 - stepY) / 2) / rayDirY);
		    }

		    //Calculate height of line to draw on screen
		    int lineHeight = abs(int(SCREEN_HEIGHT / perpWallDist));

		    //calculate lowest and highest pixel to fill in current stripe
		    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		    if (drawStart < 0) drawStart = 0;
		    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		    if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		    //choose wall color
		    sf::Color color;
		    switch(this->worldMap[mapX][mapY]) {
			    case 1:  color = sf::Color::Red;    break;
	            case 2:  color = sf::Color::Green;  break;
	            case 3:  color = sf::Color::Blue;   break;
	            case 4:  color = sf::Color::White;  break;
	            default: color = sf::Color::Yellow; break;
		    }

		    //give x and y sides different brightness
		    if (side == 1) {
				color = sf::Color(color.r/2, color.g/2, color.b/2);
		    }
		    sf::Vertex vertices[2] = {
			sf::Vertex(sf::Vector2f(x,drawStart),color),
			sf::Vertex(sf::Vector2f(x,drawEnd),color)

		    };
		    this->data->window.draw(vertices, 2, sf::Lines);
		}
		this->data->window.display();
    }
}
