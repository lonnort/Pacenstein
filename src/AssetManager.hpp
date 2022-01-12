#pragma once

#include <SFML/Graphics.hpp>
#include <map>

namespace Pacenstein {
    class AssetManager {
    public:
        AssetManager(){}
        ~AssetManager(){}

        void loadTexture(std::string name, std::string file);
        void loadFont   (std::string name, std::string file);

        sf::Texture& getTexture(std::string name);
        sf::Font&    getFont   (std::string name);

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font>    fonts;
    };
}
