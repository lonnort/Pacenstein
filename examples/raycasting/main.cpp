#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <sstream>

#define mapWidth 21
#define mapHeight 19

std::string ConvertToString(int number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

int worldMap[mapWidth][mapHeight]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,3,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,3,1},
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
    {1,3,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,3,1},
    {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main()
{

    int w = 1024, h = 576;

    double posX = 9, posY = 16;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML window", sf::Style::Default, sf::ContextSettings(24,8,8));

    window.setFramerateLimit(60);
    sf::Clock clock = sf::Clock();
    sf::Time fps;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
        // Close window: exit
        if (event.type == sf::Event::Closed)
            window.close();

        // Escape key: exit
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            window.close();
        }

        window.clear();

        for(int x = 0; x < w; x++)
        {
        //calculate ray position and direction
        double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
        double rayPosX = posX;
        double rayPosY = posY;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

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

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (rayPosX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (rayPosY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
        }

        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
                //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
        if (side == 0)
            perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        else
            perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

        //Calculate height of line to draw on screen
        int lineHeight = abs(int(h / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if(drawEnd >= h)drawEnd = h - 1;

        //choose wall color
        sf::Color color;
        switch(worldMap[mapX][mapY])
        {
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

        //draw the pixels of the stripe as a vertical line
        //verLine(x, drawStart, drawEnd, color);

        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(x, drawStart), color),
            sf::Vertex(sf::Vector2f(x, drawEnd), color)
        };
        window.draw(line , 2, sf::Lines);

        }

        fps = clock.getElapsedTime();
        float fpsValue = 1000000/fps.asMicroseconds();
        clock.restart();

        double moveSpeed = fps.asSeconds() * 5.0; //the constant value is in squares/second
        double rotSpeed = fps.asSeconds() * 3.0; //the constant value is in radians/second

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
        }

        window.display();
        window.clear();
    }

    return EXIT_SUCCESS;
}
