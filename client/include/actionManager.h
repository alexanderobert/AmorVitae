#ifndef CLIENT_ACTIONMANAGER_H
#define CLIENT_ACTIONMANAGER_H

#include <SFML/Graphics.hpp>

#include "clientConnection.h"

#include "actionServer.h"

class actionManager {
public:
    void pollEvent(sf::RenderWindow &, clientConnection &, actionServer &, bool &);
};


#endif //CLIENT_ACTIONMANAGER_H
