#include <graphicsManager.h>
#include <struct_Config.h>
#include <iostream>

void graphicsManager::drawMap(const std::string &mapCode, int state) {
    int radius = 45;

    sf::Texture texture;
    if (!texture.loadFromFile("../graphics/textures/background.jpg")) {
        std::cout << "texture load failed" << std::endl;
    }

    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setTexture(&texture);
    window->draw(background);

    for (int i = 0; i < state; ++i) {
        sf::CircleShape stage(
                float(radius * (state - i)),
                50
        );
        stage.setPosition(
                window->getSize().x / 2 - radius * (state - i),
                window->getSize().y / 2 - radius * (state - i)
        );
        stage.setFillColor(mapColors[i]);
        window->draw(stage);
    }
}

graphicsManager::graphicsManager(struct Config _config) {
    config = _config;
    window = new sf::RenderWindow(sf::VideoMode(config.windowWidth, config.windowHeight), "SFML works!");
    open = true;
    mapStage = -1;

    mapColors.emplace_back(sf::Color::White);// TODO Расчитывать градиент
    mapColors.emplace_back(sf::Color(204, 227, 249));
    mapColors.emplace_back(sf::Color(153, 200, 244));
    mapColors.emplace_back(sf::Color(102, 172, 239));
    mapColors.emplace_back(sf::Color(0, 118, 229));

}

bool graphicsManager::isOpen() {
    return open;
}

void graphicsManager::close() {
    window->close();
    open = false;
}

void graphicsManager::handleEvent() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            close();
        }
    }
}

void graphicsManager::clear(){
    window->clear();
}



//void graphicsManager::drawPlayer(struct Player playerData) {
//
//}
//
//void graphicsManager::drawProjectile(struct ProjectileData projectileData) {
//
//}
