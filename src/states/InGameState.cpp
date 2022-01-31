#include "Definitions.hpp"
#include "InGameState.hpp"
#include "PauseState.hpp"
#include "HuntingState.hpp"
#include "ScatterState.hpp"
#include "Definitions.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>

namespace Pacenstein {
    InGameState::InGameState(game_data_ref_t data):
        data(data),
        player(data)
    {
        w = std::stoi(data->settings.at("window").at("Width"));
        h = std::stoi(data->settings.at("window").at("Height"));
        ZBuffer.reserve(std::stoi(data->settings.at("window").at("Width")));
    }
    
    void InGameState::init() {
        this->data->score = 0;
        this->data->lives = 3;
        this->data->ghostsEaten = 0;
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

    void InGameState::move(const std::string& direction) {
        const auto worldMap = this->data->assets.getImage("Map");

        if (direction == "left")  player.moveLeft();
        if (direction == "right") player.moveRight();
        if (direction == "up")    player.moveUp(worldMap);
        if (direction == "down")  player.moveDown(worldMap);
    }
    
    void InGameState::sortSprites(std::vector<int> &order, std::vector<float> &dist, int size) {
	int gap = size;
	bool flag = true;
	while (gap != 1 || flag){
	    gap = (gap * 10) / 13;
	    if (gap < 1){
		gap = 1;
	     }
	    flag = false;
	    for (int i = 0; i < size - gap; i++){
		int j = i + gap;
                if (dist[i] < dist[j]){
                    std::swap(dist[i],dist[j]);
                    std::swap(order[i],order[j]);
                    flag = true;
                }
	    }
	}
    }

    
    void InGameState::drawWalls(map_t worldMap, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f plane) {
        double positionX = position.x;
        double positionY = position.y;

        double directionX = direction.x;
        double directionY = direction.y;

        double planeX = plane.x;
        double planeY = plane.y;

        double textureSectionX;
        sf::Sprite WallTexture;

        double scaleY;
        int scaleX;

        int LastMapX = -1, LastMapY = -1;
        int LastSide = -1;
        int Repeats = 0;

        for(int x = 0; x < w; x++) {
            //calculate ray position and direction
            double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
            double rayPosX = positionX;
            double rayPosY = positionY;
            double rayDirX = directionX + planeX * cameraX;
            double rayDirY = directionY + planeY * cameraX;

            //which box of the map we're in
            int mapX = int(rayPosX);
            int mapY = int(rayPosY);

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

            bool hit = false; //was there a wall hit?
            bool side = true; //was a NS or a EW wall hit?

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
            while (!hit) {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = false;
                }
                else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = true;
                }

                //Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0) hit = true;
            }

            //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
            if (!side) {
                perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
                while (rayPosY > 1) {
                    rayPosY = -1;
                }
                textureSectionX = rayPosY;
            }
            else {
                perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

                while (rayPosX > 1) rayPosX =- 1;
                textureSectionX = rayPosX;
            }

            if (textureSectionX < 0) textureSectionX = fabs(textureSectionX);

            //Calculate height of line to draw on screen
            float lineHeight = abs(int(h / perpWallDist));
            scaleY = lineHeight / 64;
            scaleX = worldMap[mapX][mapY] / 64;

            //Calculate height of line to draw on screen
            if (scaleX < 1) scaleX = 1;

            switch (worldMap[mapX][mapY]) {
                case 1:  WallTexture.setTexture(wallTexture); break;
                case 2:  WallTexture.setTexture(doorTexture); break;
                // case 3:  WallTexture.setTexture(wallTexture); break;
                // case 4:  WallTexture.setTexture(wallTexture); break;
                default: WallTexture.setTexture(wallTexture); break;
            }

            if (LastMapY == mapY && LastMapX == mapX && side == LastSide) Repeats++;
            else Repeats = 0;

            textureSectionX = textureSectionX + Repeats;

            //give x and y sides different brightness
            if (side) {
                WallTexture.setColor(sf::Color(148,148,148,255));
                textureSectionX = 64 - textureSectionX;
            }

	    // original value was 288 instead of 540
	    // float y = 540 - (64 * scaleY) / 2;
	    float y = 360 - (64 * scaleY) / 2;


            //Draw the walls
            WallTexture.setScale(1, scaleY);
            WallTexture.setTextureRect(sf::IntRect(textureSectionX,0,1,64));

            int drawTexture = 0;
            while (drawTexture < scaleX) {
                WallTexture.setPosition(x, y);
                this->data->window.draw(WallTexture);
                drawTexture++;
                x++;
            }
            x--;

            WallTexture.setColor(sf::Color(255, 255, 255, 255));

            LastMapY = mapY;
            LastMapX = mapX;
            LastSide = side;

            //SET THE ZBUFFER FOR THE SPRITE CASTING
            this->ZBuffer[x] = perpWallDist; //perpendicular distance is used
        } // end for-loop for wall casting
    }

    void InGameState::drawEntities(std::vector<Sprite> sprites, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f plane) {
        double positionX = position.x;
        double positionY = position.y;

        double dirX = direction.x;
        double dirY = direction.y;

        double planeX = plane.x;
        double planeY = plane.y;

        std::vector<int>   spriteOrder;
        std::vector<float> spriteDistance;

	// for (uint i = 0; i < sprites.size(); ++i) {
        //     float dist = ((positionX - sprites[i].x) * (positionX - sprites[i].x) + (positionY - sprites[i].y) * (positionY - sprites[i].y));
        //     spriteOrder.push_back(i);
        //     spriteDistance.push_back(dist); // sqrt not taken, uneeded
        // }
	// sortSprites(spriteOrder, spriteDistance, spriteOrder.size());

	int counter = 0;
	for (auto sprite : sprites ) {
	    counter++;
	    float dist = ((positionX - sprite.x) * (positionX - sprite.x) + (positionY - sprite.y) * (positionY - sprite.y));
	    spriteOrder.push_back(counter);
            spriteDistance.push_back(dist); // sqrt not taken, uneeded
	}
	sortSprites(spriteOrder, spriteDistance, spriteOrder.size());

        //after sorting the sprites, do the projection and draw them
	for (auto sprite : sprites ) {
            //translate sprite position to relative to camera
	    double spriteX = sprite.x - positionX;
	    double spriteY = sprite.y - positionY;

            //transform sprite with the inverse camera matrix
            // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
            // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
            // [ planeY   dirY ]                                          [ -planeY  planeX ]

            double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

            double transformX = invDet * (dirY * spriteX - dirX * spriteY);
            double transformY = (invDet * (-planeY * spriteX + planeX * spriteY)) * 0.9; //this is actually the depth inside the screen, that what Z is in 3D

	    // if object is not visible, skip it.
            if (transformY < 0) continue;

            int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

            //calculate height of the sprite on screen
            int spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye

            //calculate lowest and highest pixel to fill in current stripe
            int drawStartY = -spriteHeight / 2 + h / 2;
            if(drawStartY < 0) drawStartY = 0;

            int drawEndY = spriteHeight / 2 + h / 2;
            if(drawEndY >= h) drawEndY = h - 1;

            //calculate width of the sprite
            int spriteWidth = abs(int(h / (transformY)));
            int drawStartX = -spriteWidth / 2 + spriteScreenX;
            int drawEndX = spriteWidth / 2 + spriteScreenX;

            int drawWidth = drawEndX - drawStartX;
            int drawOrigStartX = drawStartX;

            int texture_width = 16;
            int texture_height = 16;

            int spriteLeft = 0;
            int spriteRight = texture_width;
            int spriteTop = 0;
            int spriteBottom = texture_height;

            int width = w;

            if (drawStartX > width || drawEndX < 0) continue;

            //loop through every vertical stripe of the sprite on screen
            for (int stripe = drawStartX; stripe <= drawEndX; ++stripe) {
                if (stripe < 0) {
                    drawStartX += 1;
                    continue;
                }
                // are other walls in front
                if (transformY > this->ZBuffer[stripe]) {
                    drawStartX += 1;
                    continue;
                }
                break;
            }

            int newWidth = drawEndX - drawStartX;
            float d = (float)drawWidth / (float)newWidth;

            spriteLeft = texture_width - (float)texture_width / d;

            for (int stripe = drawEndX; stripe > drawStartX; --stripe) {
                if (stripe > width) {
                    drawEndX -= 1;
                    continue;
                }
                if (transformY > this->ZBuffer[stripe]) {
                    drawEndX -= 1;
                    continue;
                }
                break; // y break, de continues snap ik, maar deze is niet nodig
            }

            newWidth = drawEndX - drawOrigStartX;
            d = (float)drawWidth / (float)newWidth;

            spriteRight = (float)texture_width / d;

            sf::VertexArray spriteQuad(sf::Quads, 4);

            spriteQuad[0].position  = sf::Vector2f(drawStartX,  drawStartY);
            spriteQuad[0].texCoords = sf::Vector2f(spriteLeft,  spriteTop);
            spriteQuad[1].position  = sf::Vector2f(drawEndX,    drawStartY);
            spriteQuad[1].texCoords = sf::Vector2f(spriteRight, spriteTop);
            spriteQuad[2].position  = sf::Vector2f(drawEndX,    drawEndY);
            spriteQuad[2].texCoords = sf::Vector2f(spriteRight, spriteBottom);
            spriteQuad[3].position  = sf::Vector2f(drawStartX,  drawEndY);
            spriteQuad[3].texCoords = sf::Vector2f(spriteLeft,  spriteBottom);

            this->data->window.draw(spriteQuad, &sprite.tex);
	}
    }

    void InGameState::draw(float dt) {
        if (!this->wallTexture.loadFromFile  ((TEXTURES_FILEPATH "wall.png"))
        ||  !this->doorTexture.loadFromFile  ((TEXTURES_FILEPATH "door.png"))
        ||  !this->blinkyTexture.loadFromFile((GHOSTS_FILEPATH "blinky_middle_one.png"))
        ||  !this->clydeTexture.loadFromFile ((GHOSTS_FILEPATH "clyde_middle_two.png"))
        ||  !this->pacTexture.loadFromFile   ((PELLET_FILEPATH "pac.png"))) {
            std::cout << "Failed to load texture!" << '\n';
        }

        this->data->window.clear();

        const auto worldMap = this->data->assets.getImage("Map");

        std::vector<Sprite> sprites = {
	    {1.5, 3.5,  blinkyTexture},
	    {4.5, 15.5, clydeTexture},
	    {4.5, 3.5, clydeTexture},
            {4.5, 4.5,  pacTexture},
            {4.5, 5.5,  pacTexture},
            {4.5, 6.5,  pacTexture},
	    {4.5, 7.5,  pacTexture},
	    {4.5, 8.5,  pacTexture},
	    {4.5, 9.5,  pacTexture},
	    {4.5, 10.5, pacTexture},
	    {4.5, 11.5, pacTexture},
	    {4.5, 12.5, pacTexture},
	    {4.5, 13.5, pacTexture},
	    {4.5, 14.5, pacTexture},

        };

        // for(int i = 0; i < worldMap.size(); i++){
        //     for(int j = 0; j < worldMap[i].size(); j++){
        //         switch (worldMap[i][j]){
        //         case 2:
        //             sprites.push_back({0.5 + j, 0.5 + i, pacTexture});
        //             break;
                
        //         case 4:
        //             break;
        //             sprites.push_back({0.5 + j, 0.5 + i, pacTexture});
        //         }
        //     }
        // }

        sf::Vector2f position  = player.getPos();
        sf::Vector2f direction = player.getDir();
        sf::Vector2f plane     = player.getPlane();

        drawWalls   (worldMap, position, direction, plane);
        drawEntities(sprites,  position, direction, plane);

        this->fps = this->clock.getElapsedTime();
        this->clock.restart();

        player.setMoveSpeed(fps.asSeconds() * 20.0); //the constant value is in squares/second
        player.setRotSpeed (fps.asSeconds() * 20.0); //the constant value is in radians/second
        
        sf::Text scoreText("Score: " + std::to_string(this->data->score), this->data->assets.getFont("Font"));
        scoreText.setPosition(5, 5);
        this->data->window.draw(scoreText);

        sf::Text livesText("Lives: ", this->data->assets.getFont("Font"));
        livesText.setPosition(5, std::stoi(this->data->settings.at("window").at("Height")) - livesText.getGlobalBounds().height - 25);
        this->data->window.draw(livesText);

        for(uint i = 0; i < this->data->lives; i++){
            sf::Sprite heart;
            heart.setTexture(this->data->assets.getTexture("Heart"));
            heart.setPosition(
                livesText.getGlobalBounds().width + (10 + heart.getGlobalBounds().width) * i,
                std::stoi(this->data->settings.at("window").at("Height")) - heart.getGlobalBounds().height - 5
            );
            this->data->window.draw(heart);
        }

        this->data->window.display();
    }
}
