#ifndef CLIENT_DISPLAYMANAGER_H
#define CLIENT_DISPLAYMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ifaddrs.h>
#include <cstring>

#include <iostream>

#include "json.hpp"

using json = nlohmann::json;

struct Model {
    int height;
    int width;
};

struct Point {
    int x;
    int y;
};

struct Vector {
    Point from, to;
};

//тип отображаемого объекта
enum typeOfObject {
    player,
    map,
    obstruction
};

struct PlayerState {
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    int flying_tick;
    State state_;
};

struct Player {
    Vector sight;
    PlayerState state_;
    int speed;

    PlayerState playerState;
};

struct Map {
    int layers_count;
    double ring_radius;
};

struct Obstruction {

};

//категория объекта
enum Type {
    STATIC_OBJECT,
    PLAYER_OBJECT,
    BULLET_OBJECT
};

//Объект получаемый от сервера
struct Object {

    Point position;
    Model model;
    Type type;

    Player player;
    Map map;
    Obstruction obstruction;
};

//сообщение от сервера
struct MessageFromServer {
    typeOfObject type;
    Object object;
};


class displayManager {

private:
    Point position;
    Vector sight;

public:
    void playerDataToGraph(struct MessageFromServer);
    void projectFileDataToGraph(struct MessageFromServer);
    void mapCodeToGraph(struct MessageFromServer);
    void configToGraph(struct MessageFromServer);
};

#endif //CLIENT_DISPLAYMANAGER_H
