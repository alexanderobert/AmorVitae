#ifndef GRAPHIC_MANAGER_H
#define GRAPHIC_MANAGER_H

#include <SFML/Graphics.hpp>
#include "struct_Config.h"

#include <PlayerModel.h>

#include <actionManager.h>

#include <ProjectileModel.h>

#include <Menu.h>

#include <unordered_map>

class GraphicsManager {
public:
    void drawMap(const std::vector<MapInterface> &map);

    void object(const std::vector<std::shared_ptr<ObjectInterface>> &objects);

    void drawPlayer(const std::vector<PlayerInterface> &playerData);

    void drawObstacle(const std::vector<ObstructionInterface> &obstacleData);
//
    void drawProjectile(const std::vector<BulletInterface> &);

    explicit GraphicsManager(Config config, actionManager &);

    void handleEvent(actionManager &, actionServer &);

    void displayMainMenu();

    void displayWin();

    void displayLose();

    bool isOpen() const;

    void close();

    void clear();

    void display(){
        window->display();
    }

    void setMyID(int ID){ myID = ID; }

private:
    sf::RenderWindow *window;
    Menu *menu;

    struct Config config;
    bool open;
    int myID;
    std::vector<sf::Color> mapColors;

    sf::RectangleShape background;
    sf::Texture background_texture;
    sf::Texture player_texture;
    sf::Texture bullet_texture;

};

#endif