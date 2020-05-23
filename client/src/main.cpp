#include <SFML/Graphics.hpp>
#include <iostream>

#include <actionManager.h>
#include <actionServer.h>

#include <graphicsManager.h>
#include <struct_Config.h>

int main() {
    actionServer action;
    actionManager user;

    Config configWindow;
    user.defineResolution(configWindow);

    action.connectClient();

    graphicsManager graph(configWindow, user);


    while(graph.isOpen()){

        auto objects = action.getMessage();

        graph.object(objects);

        action.updatePosition(objects);

        graph.handleEvent(user, action);

        graph.display();

    }

    return 0;
}
