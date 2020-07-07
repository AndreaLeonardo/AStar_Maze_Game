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
    MapSearchNode GoalNode(10, 10);

    Player player(16 + 32 * StartNode.x, 16 + 32 * StartNode.y, sf::Vector2u(3, 18), "../sprite/pinguino.png", 0.01f);

    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    unsigned int ss;
    findpathalg(&player, StartNode, GoalNode, &ss, &astarsearch, &NumSearches);

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


        player.Update(deltaTime, GoalNode);
        window.clear();
        drawMap(window, GoalNode);
        player.draw(window);
        window.display();

    }


}