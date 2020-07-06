#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "findpath.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(640, 640), "ASTAR ALGORITHM");

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

    }


}