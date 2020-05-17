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

    action.myId = action.connectClient();

    graphicsManager graph(configWindow);

    int state = 5;
    const std::string mapCode = "a";

    double delta = 0.0;

    while(graph.isOpen()){

        auto objects = action.getMessage();

        PointInterface pos(480.0 + delta, 360.0 + delta);
        ModelInterface mod(15,15);
        PlayerInterface player(static_cast<ObjectInterface::Type>(Type::PLAYER_OBJECT), 1, pos, mod);

        PointInterface pos2(570.0 - delta, 500 - delta);
        ModelInterface mod2(15,15);
        PlayerInterface player2(static_cast<ObjectInterface::Type>(Type::PLAYER_OBJECT), 2, pos2, mod2);

        ModelInterface iMod(15,15);
        PlayerInterface iPlayer(static_cast<ObjectInterface::Type>(Type::PLAYER_OBJECT), 15, action.myPosition, iMod);

        ModelInterface iMod2(3,3);
        PlayerInterface iSight(static_cast<ObjectInterface::Type>(Type::PLAYER_OBJECT), 100, action.mySight.to, iMod2);

        std::vector<struct PlayerInterface> players;

        PointInterface pos3(720.0, 370.0);
        ModelInterface mod3(100,10);
        ObjectInterface obstruct(ObjectInterface::Type::STATIC_OBJECT, 3, pos3, mod3);

        PointInterface pos4(750.0, 200.0);
        ModelInterface mod4(10,150);
        ObjectInterface obstruct2(ObjectInterface::Type::STATIC_OBJECT, 4, pos4, mod4);

        PointInterface pos5(770.0, 300.0);
        ModelInterface mod5(10,70);
        ObjectInterface obstruct3(ObjectInterface::Type::STATIC_OBJECT, 5, pos5, mod5);

        PointInterface pos6(860.0, 500.0);
        ModelInterface mod6(80,10);
        ObjectInterface obstruct4(ObjectInterface::Type::STATIC_OBJECT, 6, pos6, mod6);

        std::vector<struct ObjectInterface> obstructs;

        players.push_back(player);
        players.push_back(player2);
        players.push_back(iPlayer);
        players.push_back(iSight);

        obstructs.push_back(obstruct);
        obstructs.push_back(obstruct2);
        obstructs.push_back(obstruct3);
        obstructs.push_back(obstruct4);

        graph.handleEvent(user, action);
        graph.drawMap(mapCode, state);

        graph.drawObstacle(obstructs);

        graph.drawPlayer(players);

        graph.display();

        delta+=0.05;
    }

    return 0;
}