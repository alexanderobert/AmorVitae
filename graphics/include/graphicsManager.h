#ifndef GRAPHIC_MANAGER_H
#define GRAPHIC_MANAGER_H

#include <SFML/Graphics.hpp>
#include "struct_Config.h"

#include <PlayerModel.h>

#include <actionManager.h>

#include <ProjectileModel.h>

class graphicsManager {
public:
    int init(struct Config);

    void drawMap(const std::vector<MapInterface> &map);

    void object(const std::vector<std::shared_ptr<ObjectInterface>> &objects);

    void drawPlayer(const std::vector<PlayerInterface> &playerData);

    void drawObstacle(const std::vector<ObstructionInterface> &obstacleData);
//
    void drawProjectile(const std::vector<BulletInterface> &);

    explicit graphicsManager(Config config);

    void handleEvent(actionManager &, actionServer &);

    void displayMainMenu();

    void displayPauseScreen();

    bool isOpen() const;

    void close();

    void clear();

    void display(){
        window->display();
    }

private:
    sf::RenderWindow *window;
    struct Config config;
    bool open;
    std::vector<sf::Color> mapColors;

};

#endif