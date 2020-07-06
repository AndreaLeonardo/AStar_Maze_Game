//
// Created by Andrea on 06/07/2020.
//

#ifndef LAB_PROJECT_PLAYER_H
#define LAB_PROJECT_PLAYER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "findpath.h"
#include <SFML/Graphics.hpp>

class Player{
public:
    Player(int x, int y, sf::Vector2u txt, const char s[], float mt): x(x), y(y), moveTime(mt){

        texture.loadFromFile(s);

        textureSizeP = texture.getSize();
        textureSizeP.x /= txt.x;
        textureSizeP.y /= txt.y;
        body.setSize(sf::Vector2f(32, 32));
        body.setTexture(&texture);
        body.setTextureRect(sf::IntRect(textureSizeP.x * 1, textureSizeP.y * 0, textureSizeP.x, textureSizeP.y));
        body.setOrigin(16, 18);
        body.setPosition(x, y);

        totalTime = 0.0f;
        count = 0;

    }
    ~Player(){}

    void draw(sf::RenderWindow& window){
        window.draw(body);
    }

    void move(const sf::Vector2f movement){
        body.setPosition(movement);
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        Player::x = x;
    }

    void setY(int y) {
        Player::y = y;
    }

    bool newPath(){
        if (NewPath)
            count = 0;
        c = 3;
    }

public:
    std::vector<MapSearchNode*> directions;
    sf::RectangleShape body;
    bool NewPath = false;

private:
    int x, y;
    sf::Texture texture;
    sf::Vector2u textureSizeP;
    float moveTime;
    float totalTime;
    int count;
    int c = 3;
    int ic = 0;
    bool isGoal = false;


};


#endif //LAB_PROJECT_PLAYER_H
