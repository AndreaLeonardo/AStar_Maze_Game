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

    void Update(float DeltaTime, MapSearchNode GN){

        totalTime += DeltaTime;

        if(totalTime > moveTime && this->count < directions.size()){
            totalTime-= moveTime;
            if (ic > 2){
                ic = 0;
            }

            if(body.getPosition().x == (16+32*GN.x) && body.getPosition().y == (16+32*GN.y) && !NewPath){
                body.setTextureRect(sf::IntRect(textureSizeP.x * ic, textureSizeP.y * 0, textureSizeP.x, textureSizeP.y));
                ic++;

            }

            if(body.getPosition().x == (16+32*directions[count]->x) && body.getPosition().y == (16+32*directions[count]->y) && this->count < directions.size()-1){
                count++;
                c = 3;

            }

            if(body.getPosition().x != (16+ 32*directions[count]->x) && body.getPosition().y == (16+32*directions[count]->y)) {

                if(body.getPosition().x > (16+ 32*directions[count]->x)) {
                    move(sf::Vector2f((16 + 32 * directions[count]->x) + 8 * c, (16 + 32 * directions[count]->y)));
                    body.setTextureRect(sf::IntRect(textureSizeP.x * ic, textureSizeP.y * 11, textureSizeP.x,
                                                    textureSizeP.y));
                }
                else {
                    move(sf::Vector2f((16 + 32 * directions[count]->x) - 8 * c, (16 + 32 * directions[count]->y)));
                    body.setTextureRect(sf::IntRect(textureSizeP.x * ic, textureSizeP.y * 2, textureSizeP.x,
                                                    textureSizeP.y));
                }
                ic++;
                c--;

            }
            else if (body.getPosition().x == (16+ 32*directions[count]->x) && body.getPosition().y != (16+32*directions[count]->y)){
                if(body.getPosition().y > (16+32*directions[count]->y))
                    move(sf::Vector2f((16 + 32 * directions[count]->x), (16 + 32 * directions[count]->y) + 8 * c));
                else
                    move(sf::Vector2f((16 + 32 * directions[count]->x), (16 + 32 * directions[count]->y) - 8 * c));
                body.setTextureRect(sf::IntRect(textureSizeP.x*ic, textureSizeP.y*2, textureSizeP.x, textureSizeP.y));
                ic++;
                c--;
            }

        }

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
