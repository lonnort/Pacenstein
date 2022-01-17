#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <map>

namespace Pacenstein {
    class AssetManager {
    public:
        AssetManager(){}
        ~AssetManager(){}

        void loadTexture(std::string name, std::string file);
        void loadFont   (std::string name, std::string file);
	void loadVertex ();

        sf::Texture& getTexture(std::string name);
        sf::Font&    getFont   (std::string name);
	sf::Vertex&  getVertex (std::string name);

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font>    fonts;
        std::map<std::string, sf::Vertex>  vertexes;
    };
}
