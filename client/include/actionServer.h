#ifndef CLIENT_ACTIONSERVER_H
#define CLIENT_ACTIONSERVER_H

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


//блок формирования сообщения для отправки
enum EventType {
    move,
    blink,
    changeSight
};

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct MousePosition {
    int x;
    int y;
};

struct Model {
    int height;
    int width;
};

struct Point {
    double x;
    double y;
};

struct Vector {
    Point from, to;
};


struct MessageToServer  {
    EventType type; //move, blink, change sight
    Direction direction;
    MousePosition newSight;
};
//конец блока формирования сообщения для отправки

//блок формирования получения сообщения


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

//конец блока формирования получения сообщения

//класс для отправки и получения
class actionServer {

public:
    void getActionKey(std::string);
    void getActionMousePos(int, int);

    void sendActionMove(Direction);
    void sendActionBlink();
    void sendActionChangeSight(int, int);

    MessageFromServer getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
