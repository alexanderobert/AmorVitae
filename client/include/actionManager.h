#ifndef CLIENT_ACTIONMANAGER_H
#define CLIENT_ACTIONMANAGER_H

#include <SFML/Graphics.hpp>

#include "clientConnection.h"

#include "actionServer.h"

class actionManager {
public:
    void sendMove(actionServer &action, Direction); //при нажатии WASD
    void sendBlink(actionServer &action); //при нажатии Space

    void actionUser(sf::RenderWindow &window, sf::Event &, actionServer &);
};


#endif //CLIENT_ACTIONMANAGER_H
