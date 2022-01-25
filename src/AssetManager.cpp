#include "AssetManager.hpp"

#include <fstream>
#include <iostream>

namespace Pacenstein {
    void AssetManager::loadTexture(std::string name, std::string file) {
        sf::Texture tex;
        if (tex.loadFromFile(file)) this->textures[name] = tex;
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
    std::vector<std::string>& AssetManager::getCsvFile (std::string name) { return this->csv_files.at(name); }
    std::vector<std::string>& AssetManager::getConfFile (std::string name) { return this->conf_files.at(name); }

    void AssetManager::saveCsvFile(std::string name, std::string fileName, std::vector<std::string> newContent) {
        std::ofstream file;
        file.open(fileName);
        if(file.is_open()){
            for(auto line : newContent){
                file << line;
                file << "\n";
            }
            file.close();
        }else{
            std::cout << "error with opening file!\n";
        }
        this->loadCsvFile(name, fileName);
    }
}
