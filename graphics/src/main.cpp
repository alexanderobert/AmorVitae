#include <SFML/Graphics.hpp>
#include <iostream>
//#include "graphics/include/drawobject.h"

void graph() { //main Глеба
    int windowWidth = 640;
    int windowHeight = 480;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");

    system("dir");

    sf::Texture texture;
    if (!texture.loadFromFile("../graphics/textures/background.jpg")) {
        std::cout << "texture load failed" << std::endl;
    }

    //sf::Sprite sprite(texture);

    //sf::CircleShape shape(100.f);

    //shape.setFillColor(sf::Color::Green);
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setTexture(&texture);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.display();
    }
}