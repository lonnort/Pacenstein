#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <map>
#include <vector>
#include <string>

namespace Pacenstein {
    class AssetManager {
    public:
        AssetManager(){}
        ~AssetManager(){}

        void loadTexture (std::string name, std::string file);
        void loadFont    (std::string name, std::string file);
        void loadTextFile(std::string name, std::string file);
	void loadVertex  (std::string name, sf::Vector2f location, sf::Vector2f location_2, sf::Color);

        sf::Texture& getTexture (std::string name);
        sf::Font&    getFont    (std::string name);
	sf::Vertex&  getVertex  (std::string name);
        std::vector<std::string>& getTextFile(std::string name);

    private:
        std::map<std::string, sf::Texture>              textures;
        std::map<std::string, sf::Font>                 fonts;
        std::map<std::string, sf::Vertex>               vertexes;
        std::map<std::string, std::vector<std::string>> files;
    };
}
