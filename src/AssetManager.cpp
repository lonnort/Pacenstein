#include "AssetManager.hpp"

#include <fstream>
#include <iostream>

namespace Pacenstein {
    void AssetManager::loadTexture(std::string name, std::string file) {
        sf::Texture tex;
        if (tex.loadFromFile(file)) this->textures[name] = tex;
    }

    void AssetManager::loadTexture(std::string name, sf::Texture file) {
        this->textures[name] = file;
    }

    void AssetManager::loadFont(std::string name, std::string file) {
        sf::Font font;
        if (font.loadFromFile(file)) this->fonts[name] = font;
    }

    void AssetManager::loadCsvFile(std::string name, std::string file) {
        std::string str;
        std::ifstream input(file);
        this->csv_files[name].clear();
        while (getline(input, str)) this->csv_files[name].push_back(str);
        input.close();
    }

    void AssetManager::loadImage(std::string name, std::string file) {
        sf::Image map_img;
        map_img.loadFromFile(file);

        this->images[name].fill({0});

        for (int x = 0; x < MAP_WIDTH; x++) {
            for (int y = 0; y < MAP_HEIGHT; y++) {
                sf::Color pixel = map_img.getPixel(x, y);
                if      (pixel == sf::Color(255, 255, 255)) this->images.at(name).at(x).at(y) = 0;
                else if (pixel == sf::Color(255,   0,   0)) this->images.at(name).at(x).at(y) = 1;
                else if (pixel == sf::Color(  0, 255,   0)) this->images.at(name).at(x).at(y) = 2;
                else if (pixel == sf::Color(  0,   0, 255)) this->images.at(name).at(x).at(y) = 3;
                else if (pixel == sf::Color(255, 255,   0)) this->images.at(name).at(x).at(y) = 4;
                else this->images.at(name).at(x).at(y) = 5;
            }
        }
    }

    void AssetManager::loadConfFile(std::string name, std::string file) {
        std::string str;
        std::ifstream input(file);
        this->conf_files[name].clear();
        while (getline(input, str)) this->conf_files[name].push_back(str);
        input.close();
    }

    void AssetManager::loadVertex(std::string name, sf::Vector2f location, sf::Color color) {
        sf::Vertex ver = sf::Vertex(location, color);
        this->vertexes[name] = ver;
    }

    sf::Texture& AssetManager::getTexture (std::string name) { return this->textures.at(name); }
    sf::Font&    AssetManager::getFont    (std::string name) { return this->fonts.at(name); }
    sf::Vertex&  AssetManager::getVertex  (std::string name) { return this->vertexes.at(name); }
    std::array<std::array<int, MAP_HEIGHT>, MAP_WIDTH>& AssetManager::getImage(std::string name) { return this->images.at(name); }
    std::vector<std::string>& AssetManager::getCsvFile (std::string name) { return this->csv_files.at(name); }
    std::vector<std::string>& AssetManager::getConfFile (std::string name) { return this->conf_files.at(name); }

    void AssetManager::saveCsvFile(std::string name, std::string fileName, std::vector<std::string> newContent) {
        std::ofstream file;
        file.open(fileName);
        if (file.is_open()) {
            for (auto line : newContent) {
                file << line;
                file << "\n";
            }
            file.close();
        }
        else std::cout << "error with opening file!\n";
        this->loadCsvFile(name, fileName);
    }
}
