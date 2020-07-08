#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "findpath.h"
#include "PLAYER.h"
#include "MAP.h"
#include "ALGORITHM.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(640, 640), "ASTAR ALGORITHM");

    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(-1, -1);

    Player player(16 + 32 * StartNode.x, 16 + 32 * StartNode.y, sf::Vector2u(3, 18), "../sprite/pinguino.png", 0.01f);

    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    unsigned int ss;

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i posMouse = sf::Mouse::getPosition(window);

            player.NewPath = true;
            player.newPath();

            StartNode.setY((player.body.getPosition().y - 16) / 32);
            StartNode.setX((player.body.getPosition().x - 16) / 32);
            if ((posMouse.x - 16) % 32 > 15)
                GoalNode.setX(((posMouse.x + (32 - (posMouse.x - 16) % 32)) - 16) / 32);
            else
                GoalNode.setX(((posMouse.x + (posMouse.x - 16) % 32) - 16) / 32);
            if ((posMouse.y - 16) % 32 > 15)
                GoalNode.setY(((posMouse.y + (32 - (posMouse.y - 16) % 32)) - 16) / 32);
            else
                GoalNode.setY(((posMouse.y + (posMouse.y - 16) % 32) - 16) / 32);

            player.directions.clear();
            findpathalg(&player, StartNode, GoalNode, &ss, &astarsearch, &NumSearches);
        }


        player.Update(deltaTime, GoalNode);
        window.clear();
        drawMap(window, GoalNode);
        player.draw(window);
        window.display();

    }


}