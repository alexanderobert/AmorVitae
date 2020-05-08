#ifndef GRAPHIC_MANAGER_H
#define GRAPHIC_MANAGER_H

#include <SFML/Graphics.hpp>

struct Config{
    int windowWidth;
    int windowHeight;

    sf::Keyboard::Key UP;
    sf::Keyboard::Key DOWN;
    sf::Keyboard::Key LEFT;
    sf::Keyboard::Key RIGHT;
};

class graphicsManager{
private:
    sf::RenderWindow *window;
    struct Config config;
public:
    int init(struct Congfig);
    int drawMap(char *mapCode, int state);
    int drawPlayer(struct player);
    int drawProjectile(struct projectileData);

    graphicsManager(sf::RenderWindow *_window);
    void displayMainMenu(struct Config);
    void displayPauseScreen(struct Config);

}

#endif