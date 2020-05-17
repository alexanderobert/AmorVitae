#ifndef GRAPHIC_MANAGER_H
#define GRAPHIC_MANAGER_H

#include <SFML/Graphics.hpp>
#include "struct_Config.h"

#include <PlayerModel.h>

#include <actionServer.h>
#include <actionManager.h>

#include <ObstacleModel.h>
#include <ProjectileModel.h>

class graphicsManager {
public:
    int init(struct Config);

    void drawMap(const std::string &mapCode, int state);

    void drawPlayer(const std::vector<PlayerInterface> &playerData);

    void drawObstacle(const std::vector<ObjectInterface> &obstacleData);
//
    void drawProjectile(const std::vector<BulletInterface> &projectileData);

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
    std::vector<PlayerModel> buff;
    std::vector<ObstacleModel> buffObstacle;
    std::vector<ProjectileModel> bulletBuff;

    sf::RenderWindow *window;
    struct Config config;
    bool open;
    int mapStage;
    std::vector<sf::Color> mapColors;

};

#endif