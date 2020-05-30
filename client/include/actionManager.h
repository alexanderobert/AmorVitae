#ifndef CLIENT_ACTIONMANAGER_H
#define CLIENT_ACTIONMANAGER_H

#include <SFML/Graphics.hpp>

#include "actionServer.h"

#include <struct_Config.h>

#include <X11/Xlib.h>
#include <unistd.h>

class actionManager {

public:
    void sendMove(actionServer &action, DirectionInterface);
    void sendBlink(actionServer &action);

    void actionUser(sf::RenderWindow &window, sf::Event &, actionServer &);
    void makeIcon(sf::RenderWindow &window);
    void defineResolution(Config &);

    bool isGame = false;
};


#endif //CLIENT_ACTIONMANAGER_H
