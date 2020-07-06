#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "findpath.h"
#include "PLAYER.h"
#include "MAP.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(640, 640), "ASTAR ALGORITHM");

    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(-1, -1);

    Player player(16 + 32 * StartNode.x, 16 + 32 * StartNode.y, sf::Vector2u(3, 18), "../sprite/pinguino.png", 0.01f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.move(sf::Vector2f(player.getX(),player.getY()-1));
            player.setY(player.getY()-1);
            if(player.getY()<0){
                player.setY(0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.move(sf::Vector2f(player.getX()-1,player.getY()));
            player.setX(player.getX()-1);
            if(player.getX()<0){
                player.setX(0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.move(sf::Vector2f(player.getX()+1,player.getY()));
            player.setX(player.getX()+1);
            if(player.getX()>640){
                player.setX(640);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.move(sf::Vector2f(player.getX(),player.getY()+1));
            player.setY(player.getY()+1);
            if(player.getY()>640){
                player.setY(640);
            }
        }

        window.clear();
        drawMap(window, GoalNode);
        player.draw(window);
        window.display();

    }


}