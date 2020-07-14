//
// Created by Andrea on 06/07/2020.
//

#ifndef LAB_PROJECT_MAP_H
#define LAB_PROJECT_MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "findpath.h"

const int cellSize = 32;
const int cellCenter = cellSize/2;


class Block {
private:
    int x, y, difficulty;
    sf::RectangleShape square;
    bool isWall = false;

public:
    Block(int x, int y, int d, sf::Texture &texture, sf::Vector2u Rect, int i, int j, bool isWall) : x(x), y(y),
                                                                                                     difficulty(d),
                                                                                                     isWall(isWall) {
        square.setSize(sf::Vector2f(cellSize, cellSize));
        square.setPosition(x, y);
        square.setOrigin(cellCenter, cellCenter);
        square.setTexture(&texture);
        square.setTextureRect(sf::IntRect(Rect.x * i, Rect.y * j, Rect.x, Rect.y));

    }

    Block(){
        square.setSize(sf::Vector2f(cellSize, cellSize));
        square.setPosition(0, 0);
        square.setOrigin(cellCenter, cellCenter);
    }


    void draw(sf::RenderWindow &window) {
        window.draw(square);
    }

    void setPosition(int x, int y) {
        square.setPosition(x, y);
    }

    int getDiffculty() {
        return difficulty;
    }
};

class BlockFactory {
public:
    BlockFactory(MapSearchNode gn): GoalNode(gn){

        MapTexture.loadFromFile("../sprite/map.png");
        sf::Vector2u textureSize = MapTexture.getSize();
        textureSize.x /= 17;
        textureSize.y /= 15;

         grassBlock = Block(cellCenter, cellCenter, 1, MapTexture, textureSize, 7, 1, false);
         whiteFlowerBlock = Block(cellCenter, cellCenter, 2, MapTexture, textureSize, 1, 2, false);
         yellowFlowerBlock = Block(cellCenter, cellCenter, 3, MapTexture, textureSize, 3, 4, false);
         purpleFlowerBlock = Block(cellCenter, cellCenter, 4, MapTexture, textureSize, 0, 4, false);
         obstacleBlock = Block(cellCenter, cellCenter, 5, MapTexture, textureSize, 8, 2, false);
         wallBlock = Block(cellCenter, cellCenter, 9, MapTexture, textureSize, 8, 0, true);
         goalBlock = Block(GoalNode.x, GoalNode.y, 0, MapTexture, textureSize, 11, 6, false);
         ladderBlockL = Block(cellCenter, cellCenter, 7, MapTexture, textureSize, 4, 5, false);
         ladderBlockR = Block(cellCenter, cellCenter, 8, MapTexture, textureSize, 5, 5, false);
    }

    Block createBlock(int i, int j){
        if (world_map[j * MAP_HEIGHT + i] < 9 && GoalNode.x == i && GoalNode.y == j)return goalBlock;
        else if (grassBlock.getDiffculty() == world_map[j * MAP_HEIGHT + i])return grassBlock;
        else if (whiteFlowerBlock.getDiffculty() == world_map[j * MAP_HEIGHT + i])return whiteFlowerBlock;
        else if (yellowFlowerBlock.getDiffculty() == world_map[j * MAP_HEIGHT + i])return yellowFlowerBlock;
        else if (purpleFlowerBlock.getDiffculty() == world_map[j * MAP_HEIGHT + i]) return purpleFlowerBlock;
        else if (obstacleBlock.getDiffculty() == world_map[j * MAP_HEIGHT + i]) return obstacleBlock;
        else if (ladderBlockL.getDiffculty() == world_map[j * MAP_HEIGHT + i]) return ladderBlockL;
        else if (ladderBlockR.getDiffculty() == world_map[j * MAP_HEIGHT + i]) return ladderBlockR;
        else return wallBlock;
    }





private:
    sf::Texture MapTexture;
    MapSearchNode GoalNode;
    Block grassBlock;
    Block whiteFlowerBlock;
    Block yellowFlowerBlock;
    Block purpleFlowerBlock;
    Block obstacleBlock;
    Block wallBlock;
    Block goalBlock;
    Block ladderBlockL;
    Block ladderBlockR;

};

void drawMap(sf::RenderWindow &window, MapSearchNode GoalNode) {

    BlockFactory BF(GoalNode);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Block currentBlock = BF.createBlock(i,j);
            currentBlock.setPosition(cellCenter + i * cellSize, cellCenter + j * cellSize);
            currentBlock.draw(window);
        }
    }
}



#endif //LAB_PROJECT_MAP_H
