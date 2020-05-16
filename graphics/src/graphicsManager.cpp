#include <graphicsManager.h>
#include <struct_Config.h>
#include <iostream>

#include <actionServer.h>
#include <actionManager.h>
#include <ProjectileModel.h>


void graphicsManager::drawMap(const std::string &mapCode, int state) {
    int radius = 75;
    int circlePoints = 50;

    sf::Texture texture;
    if (!texture.loadFromFile("../graphics/textures/background.jpg")) {
        std::cout << "texture load failed" << std::endl;
    }

    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setTexture(&texture);
    window->draw(background);

    for (int i = 0; i < state; ++i) {
        sf::CircleShape stage(
                float(radius * (state - i)), circlePoints);
        stage.setPosition(
                window->getSize().x / 2 - radius * (state - i),
                window->getSize().y / 2 - radius * (state - i)
        );
        stage.setFillColor(mapColors[i]);
        window->draw(stage);
    }
}

graphicsManager::graphicsManager(Config config) : config(config) {
    window = new sf::RenderWindow(sf::VideoMode(config.windowWidth, config.windowHeight), "AmorVitae");
    open = true;
    mapStage = -1;

    mapColors.emplace_back(sf::Color::White);// TODO Расчитывать градиент
    mapColors.emplace_back(sf::Color(204, 227, 249));
    mapColors.emplace_back(sf::Color(153, 200, 244));
    mapColors.emplace_back(sf::Color(102, 172, 239));
    mapColors.emplace_back(sf::Color(0, 118, 229));

}

bool graphicsManager::isOpen() const {
    return open;
}

void graphicsManager::close() {
    window->close();
    open = false;
}

void graphicsManager::handleEvent(actionManager &user, actionServer &action) {
    sf::Event event;
    user.actionUser(*window, event, action);
}

void graphicsManager::clear(){
    window->clear();
}

void graphicsManager::drawPlayer(const std::vector<PlayerInterface> &playerData) {
    for (PlayerInterface player : playerData) {
        PlayerModel playerModel(
                player.position.x,
                player.position.y,
                player.model.width,
                player.model.height
        );

        buff.push_back(playerModel);
    }

    sf::RenderStates renderStates;
    for (auto &it : buff)
        it.draw(*window, renderStates);

    buff.clear();
}


void graphicsManager::drawObstacle(const std::vector<ObjectInterface> &obstacleData) {
    std::vector<sf::RectangleShape> obs;

    for(ObjectInterface obstacle : obstacleData){
        sf::RectangleShape obsModel(sf::Vector2f(100, 100));
        obsModel.setPosition(sf::Vector2f(obstacle.position.x, obstacle.position.y));
        obsModel.setFillColor(sf::Color::Black);
    }

    for(const sf::RectangleShape& model : obs){
        window->draw(model);
    }
}

void graphicsManager::drawProjectile(const std::vector<BulletInterface> &projectileData) {
    std::vector<ProjectileModel> bulletBuff;

    for (BulletInterface bullet : projectileData) {
//        ProjectileModel projectileModel(
//                bullet.position.x,
//                bullet.position.y,
//                bullet.model.width,
//                bullet.model.height
//        );

//        bulletBuff.push_back(projectileModel);
    }

    sf::RenderStates renderStates;
    for (auto &it : bulletBuff)
        it.draw(*window, renderStates);

    bulletBuff.clear();
}