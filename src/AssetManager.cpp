#include "AssetManager.hpp"

namespace Pacenstein {
    void AssetManager::loadTexture(std::string name, std::string file) {
        sf::Texture tex;
        if (tex.loadFromFile(file)) this->textures[name] = tex;
    }

    void AssetManager::loadFont(std::string name, std::string file) {
        sf::Font font;
        if (font.loadFromFile(file)) this->fonts[name] = font;
    }

    sf::Texture& AssetManager::getTexture(std::string name) {
        return this->textures.at(name);
    }

    sf::Font& AssetManager::getFont(std::string name) {
        return this->fonts.at(name);
    }

    sf::Vertex& AssetManager::getVertex(std::string name) {
        return this->vertexes.at(name);
    }
}
