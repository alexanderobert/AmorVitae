#ifndef GRAPHIC_MANAGER_H
#define GRAPHIC_MANAGER_H

#include <SFML/Graphics.hpp>
#include "struct_Config.h"

class graphicsManager {
public:
    int init(struct Config);

    void drawMap(const std::string &mapCode, int state);

//    void drawPlayer(struct Player playerData);
//
//    void drawProjectile(struct ProjectileData projectileData);

    explicit graphicsManager(struct Config config);

    void handleEvent();

    void displayMainMenu();

    void displayPauseScreen();

    bool isOpen();

    void close();

    void clear();

    void display(){
        window->display();
    }

private:
    sf::RenderWindow *window;
    struct Config config;
    bool open;
    int mapStage;
    std::vector<sf::Color> mapColors;

};

#endif