#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "findpath.h"
#include "PLAYER.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(640, 640), "ASTAR ALGORITHM");

    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(-1, -1);

    Player player(16 + 32 * StartNode.x, 16 + 32 * StartNode.y, sf::Vector2u(3, 18), "D:/sprite/pinguino.png", 0.01f);

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

        window.clear();
        player.draw(window);
        window.display();

    }


}