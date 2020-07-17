//
// Created by Andrea on 06/07/2020.
//

#ifndef LAB_PROJECT_MAP_H
#define LAB_PROJECT_MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "findpath.h"
#include <memory>

const int cellSize = 32;
const int cellCenter = cellSize/2;


class Block {
private:
    int x, y;
    sf::RectangleShape square;

public:
    Block(int x, int y, int d, sf::Texture &texture, sf::Vector2u Rect, int i, int j) : x(x), y(y){

        square.setSize(sf::Vector2f(cellSize, cellSize));
        square.setPosition(x, y);
        square.setOrigin(cellCenter, cellCenter);
        square.setTexture(&texture);
        square.setTextureRect(sf::IntRect(Rect.x*i, Rect.y*j, Rect.x, Rect.y));

    }


    void draw(sf::RenderWindow &window) {
        window.draw(square);
    }


};

class BlockFactory {
public:
    BlockFactory(){

        MapTexture.loadFromFile("../sprite/map.png");
        textureSize = MapTexture.getSize();
        textureSize.x /= 17;
        textureSize.y /= 15;

    }

    std::unique_ptr<Block> createBlock(int i, int j, MapSearchNode GoalNode){

        if (world_map[j * MAP_HEIGHT + i] < 9 && GoalNode.x == i && GoalNode.y == j)  return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 0, MapTexture, textureSize, 11, 6);
        else if (1 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 1, MapTexture, textureSize, 7, 1);
        else if (2 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 2, MapTexture, textureSize, 1, 2);
        else if (3 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 3, MapTexture, textureSize, 3, 4);
        else if (4 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 4, MapTexture, textureSize, 0, 4);
        else if (5 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 5, MapTexture, textureSize, 8, 2);
        else if (7 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 7, MapTexture, textureSize, 4, 5);
        else if (8 == world_map[j * MAP_HEIGHT + i]) return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 8, MapTexture, textureSize, 5, 5);
        else return std::make_unique<Block> (cellCenter + i* cellSize, cellCenter + j*cellSize, 9, MapTexture, textureSize, 8, 0);

    }





private:
    sf::Texture MapTexture;
    sf::Vector2u textureSize;

};

void drawMap(sf::RenderWindow &window, MapSearchNode GoalNode, BlockFactory &BF) {

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {

            BF.createBlock(i,j, GoalNode)->draw(window);

        }
    }
}



#endif //LAB_PROJECT_MAP_H
