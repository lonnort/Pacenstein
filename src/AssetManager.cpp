#include "AssetManager.hpp"

#include <fstream>

namespace Pacenstein {
    void AssetManager::loadTexture(std::string name, std::string file) {
        sf::Texture tex;
        if (tex.loadFromFile(file)) this->textures[name] = tex;
    }

    void AssetManager::loadFont(std::string name, std::string file) {
        sf::Font font;
        if (font.loadFromFile(file)) this->fonts[name] = font;
    }

    void AssetManager::loadTextFile(std::string name, std::string file) {
        std::string str;
        std::ifstream input(file);
        while (getline(input, str)) this->files[name].push_back(str);
    }

    void AssetManager::loadVertex(std::string name, sf::Vector2f location, sf::Color color) {
        sf::Vertex ver = sf::Vertex(location, color);
	this->vertexes[name] = ver;
    }

    sf::Texture&              AssetManager::getTexture  (std::string name) { return this->textures.at(name); }
    sf::Font&                 AssetManager::getFont     (std::string name) { return this->fonts.at(name); }
    sf::Vertex&               AssetManager::getVertex   (std::string name) { return this->vertexes.at(name); }
    std::vector<std::string>& AssetManager::getTextFile (std::string name) { return this->files.at(name); }
}
