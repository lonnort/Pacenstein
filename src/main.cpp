#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Blinky.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720

int main() {
    Pacenstein::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacenstein");

    return 0;
}
