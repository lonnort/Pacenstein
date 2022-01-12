#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main() {
    Pacenstein::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacenstein");

    return 0;
}
