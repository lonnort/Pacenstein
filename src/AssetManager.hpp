#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Definitions.hpp"

#include <map>
#include <vector>
#include <string>
#include <array>

namespace Pacenstein {
    /**
     * The class managing assets.
     *
     * Assets are things like images, vertices, text, and everything used by the game besides code.
     * The AssetManager loads all assets when the game has just started, and allows all other classes
     * to access the assets via a selection of functions.
     */
    class AssetManager {
    public:
        /**
         * Loads textures from a file path and gives them a name to make access easier.
         *
         * \param name The name of the texture.
         * \param file The path to the file containing the texture.
         */
        void loadTexture(std::string name, std::string file);

        /**
         * Loads textures from an sf::Texture and gives them a name to make access easier.
         *
         * \param name The name of the texture.
         * \param file The file as an sf::Texture.
         */
        void loadTexture(std::string name, sf::Texture file);

        /**
         * Loads the map from a file and gives it a name to make access easier.
         *
         * The color of the pixels determines what will be drawn on the map.
         *
         * \param name The name of the image.
         * \param file The path to the file containing the image.
         */
        void loadImage(std::string name, std::string file);

        /**
         * Loads fonts and gives them a name to make access easier.
         *
         * \param name The name of the font.
         * \param file The path to the file containing the font.
         */
        void loadFont(std::string name, std::string file);

        /**
         * Loads .csv-files and gives them a name to make access easier.
         *
         * \param name The name of the file, doesn't have to be the actual filename.
         * \param file The path to the file.
         */
        void loadCsvFile(std::string name, std::string file);

        /**
         * Loads .conf-files and gives them a name to make access easier.
         *
         * \param name The name of the file, doesn't have to be the actual filename.
         * \param file The path to the file.
         */
        void loadConfFile(std::string name, std::string file);

        /**
         * Loads vertices and gives them a name to make access easier.
         *
         * \param name     The name of the vertex.
         * \param location The location of the vertex.
         * \param color    The color for the vertex.
         */
        void loadVertex(std::string name, sf::Vector2f location, sf::Color color);

        /**
         * Returns a texture by name.
         *
         * \param  name The name of the texture.
         * \return      The texture with the given name.
         */
        sf::Texture& getTexture(std::string name);

        /**
         * Returns an image by name.
         *
         * \param  name The name of the image.
         * \return      The image with the given name.
         */
        std::array<std::array<int, MAP_HEIGHT>, MAP_WIDTH>& getImage(std::string name);

        /**
         * Returns a font by name.
         *
         * \param  name The name of the font.
         * \return      The font with the given name.
         */
        sf::Font& getFont(std::string name);

        /**
         * Returns a vertex by name.
         *
         * \param  name The name of the vertex.
         * \return      The vertex with the given name.
         */
        sf::Vertex& getVertex(std::string name);

        /**
         * Returns the .csv-file by name.
         *
         * \param  name The name of the .csv-file.
         * \return      The contents of the .csv-file with the given name.
         */
        std::vector<std::string>& getCsvFile(std::string name);

        /**
         * Returns the .conf-file by name.
         *
         * \param  name The name of the .conf-file.
         * \return      The content of the .conf-file with the given name.
         */
        std::vector<std::string>& getConfFile(std::string name);

        /**
         * Saves the contents of a vector of strings to a csv file.
         *
         * \param name          The name given to the csv file in the asset manager.
         * \param fileName      The name of the csv file.
         * \param newContent    The vector with strings to write to the csv file.
         */
        void saveCsvFile(std::string name, std::string fileName, std::vector<std::string> newContent);

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font>    fonts;
        std::map<std::string, sf::Vertex>  vertexes;
        std::map<std::string, std::array<std::array<int, MAP_HEIGHT>, MAP_WIDTH>> images;
        std::map<std::string, std::vector<std::string>> csv_files;
        std::map<std::string, std::vector<std::string>> conf_files;
    };
}
