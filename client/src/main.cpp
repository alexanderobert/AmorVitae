#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/clientConnection.h"
#include "include/actionManager.h"
#include <displayManager.h>
#include <actionServer.h>

#include <graphicsManager.h>
#include <struct_Config.h>

int main() {

    clientConnection clientCon;
    actionServer action;
    actionManager launch;

    Config configWindow;
    graphicsManager graph(configWindow);

    //graph.init(config);
    //graph.graphicsManager(configWindow);

    graph.handleEvent();

    return 0;
}