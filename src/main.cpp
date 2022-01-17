#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Blinky.hpp"
#include "Definitions.hpp" 

int main() {
    Pacenstein::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacenstein");

    return 0;
}
