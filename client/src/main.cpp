#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/clientConnection.h"
#include "include/actionManager.h"
#include <displayManager.h>
#include <actionServer.h>

#include <graphicsManager.h>
#include <struct_Config.h>

#include <Object.h>

#include <PlayerModel.h>


int main() {

    clientConnection clientCon;
    actionServer action;
    actionManager launch;
    actionManager user;

    NetClient network;

    Config configWindow;

    configWindow.windowWidth = 1280; //сделать функцию определения размера окна
    configWindow.windowHeight = 800;

    //clientCon.connectClient(network);

    graphicsManager graph(configWindow);

    int state = 5;
    const std::string mapCode = "a";

    double delta = 0.0;

    while(graph.isOpen()){

        //getMessage();

        PointInterface pos(500.0 + delta, 360.0 + delta);
        ModelInterface mod(10,15);
        PlayerInterface player(static_cast<ObjectInterface::Type>(Type::PLAYER_OBJECT), 1, pos, mod);

        PointInterface pos2(540.0 - delta, 410.0 - delta);
        ModelInterface mod2(10,15);
        PlayerInterface player2(static_cast<ObjectInterface::Type>(Type::PLAYER_OBJECT), 2, pos2, mod2);

        std::vector<struct PlayerInterface> players;

        PointInterface pos3(520.0, 370.0);
        ModelInterface mod3(10,15);
        ObjectInterface obstruct(ObjectInterface::Type::PLAYER_OBJECT, 1, pos3, mod3);

        PointInterface pos4(550.0, 420.0);
        ModelInterface mod4(10,15);
        ObjectInterface obstruct2(ObjectInterface::Type::PLAYER_OBJECT, 2, pos4, mod4);

        std::vector<struct ObjectInterface> obstructs;

        players.push_back(player);
        players.push_back(player2);

        obstructs.push_back(obstruct);
        obstructs.push_back(obstruct2);

        graph.handleEvent(user, action);
        graph.drawMap(mapCode, state);

        graph.drawPlayer(players);


        graph.drawObstacle(obstructs);

        graph.display();

        delta+=0.05;
    }

    return 0;
}