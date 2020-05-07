#ifndef CLIENT_ACTIONMANAGER_H
#define CLIENT_ACTIONMANAGER_H

#include <SFML/Graphics.hpp>

#include "clientConnection.h"

#include "actionServer.h"

class actionManagerInterface {
public:
    void pollEvent(sf::RenderWindow &, clientConnectionInterface &, actionServerInterface &, bool &);
};


#endif //CLIENT_ACTIONMANAGER_H
