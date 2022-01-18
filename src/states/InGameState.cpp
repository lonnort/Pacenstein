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
	this->data->assets.loadVertex("Vertex Top", sf::Vector2f(100,0),   sf::Color::Red);
	this->data->assets.loadVertex("Vertex Bottom", sf::Vector2f(100,500),  sf::Color::Blue);
	sf::Vertex vertices[4] = {
	    this->data->assets.getVertex("Vertex Top"),
	    this->data->assets.getVertex("Vertex Bottom")
	};

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
                    case sf::Keyboard::Key::KEY_DOWN:
                    case sf::Keyboard::Key::KEY_LEFT:
                    case sf::Keyboard::Key::KEY_RIGHT:
                    case sf::Keyboard::Key::KEY_ALT_UP:
                    case sf::Keyboard::Key::KEY_ALT_DOWN:
                    case sf::Keyboard::Key::KEY_ALT_LEFT:
                    case sf::Keyboard::Key::KEY_ALT_RIGHT:
                        this->data->machine.addState(state_ref_t(std::make_unique<HuntingState>(this->data)), true);
                        break;
                }
            }
        }
    }

    void InGameState::update(float dt) {
        std::cout << "In game" << std::endl;
    }

    // Checkout https://lodev.org/cgtutor/raycasting.html for the original algoritm to generate a 2.5D world
    void InGameState::draw(float dt) {
	this->data->window.clear();
	//std::vector<sf::Vertex> vertices = {
	// loop door de hele breedte van het scherm
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	
	for (int x = 0; x < SCREEN_WIDTH; x++) {
	    //calculate ray position and direction
	    double cameraX = 2 * x / double(SCREEN_WIDTH) - 1; //x-coordinate in camera space
	    double rayDirX = dirX + planeX * cameraX;
	    double rayDirY = dirY + planeY * cameraX;
	    
	    //which box of the map we're in
	    int mapX = int(posX);
	    int mapY = int(posY);
	    
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
		sideDistX = (posX - mapX) * deltaDistX;
	    } else {
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	    } if (rayDirY < 0) {
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	    }  else {
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	    }
	    
	    //perform DDA
	    while (hit == 0)  {
		//jump to next map square, OR in x-direction, OR in y-direction
		if (sideDistX < sideDistY) {
		    sideDistX += deltaDistX;
		    mapX += stepX;
		    side = 0;
		} else {
		    sideDistY += deltaDistY;
		    mapY += stepY;
		    side = 1;
		}
                //Check if ray has hit a wall
		if (worldMap[mapX][mapY] > 0) {
		    hit = 1;
		}
	    }

	    //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
	    if (side == 0) {
		perpWallDist = fabs((mapX - posX + (1 - stepX) / 2) / rayDirX);
	    } else {
		perpWallDist = fabs((mapY - posY + (1 - stepY) / 2) / rayDirY);
	    }
	    
	    //Calculate height of line to draw on screen
	    int lineHeight = abs(int(SCREEN_HEIGHT / perpWallDist));
	    
	    //calculate lowest and highest pixel to fill in current stripe
	    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	    if(drawStart < 0)drawStart = 0;
	    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
	    if(drawEnd >= SCREEN_HEIGHT)drawEnd = SCREEN_HEIGHT - 1;
	    
	    //choose wall color
	    sf::Color color;
	    switch(worldMap[mapX][mapY]) {
	    case 1:  color = sf::Color::Red;    break; //red
            case 2:  color = sf::Color::Green;  break; //green
            case 3:  color = sf::Color::Blue;   break; //blue
            case 4:  color = sf::Color::White;  break; //white
            default: color = sf::Color::Yellow; break; //yellow
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
