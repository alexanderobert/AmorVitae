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

    configWindow.windowWidth = 1280; //сделать функцию определения размера окна
    configWindow.windowHeight = 800;

    action.connectClient();

    graphicsManager graph(configWindow);


    while(graph.isOpen()){

        auto objects = action.getMessage();

        action.updatePosition(objects);

        graph.object(objects);

        graph.handleEvent(user, action);
        graph.display();

    }

    return 0;
}
