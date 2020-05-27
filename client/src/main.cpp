#include <SFML/Graphics.hpp>
#include <iostream>

#include <actionManager.h>
#include <actionServer.h>

#include <GraphicsManager.h>
#include <struct_Config.h>

int main() {
    actionServer action;
    actionManager user;

    Config configWindow;
    user.defineResolution(configWindow);

    //action.connectClient();

    GraphicsManager graph(configWindow, user);

    while(graph.isOpen()){
        if(!user.isGame){
            graph.displayMainMenu();

        } else{
            auto objects = action.getMessage();

            graph.object(objects);

            action.updatePosition(objects);
        }

        graph.handleEvent(user, action);

        graph.display();

    }

    return 0;
}
