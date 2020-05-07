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
    blink
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


//struct MessageToServer  {
//    EventType type; //move, blink, change sight
//    Direction direction;
//    MousePosition newSight;
//};

struct Event {
    EventType type; //move, blink
    Vector sight;
};

struct Move: Event{
    Direction direction;
};

struct Blink: Event{

};

//конец блока формирования сообщения для отправки

//блок формирования получения сообщения


//тип отображаемого объекта

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
    int ID;
};

struct Player:Object {
    Vector sight;
    int speed;
};

struct PlayerState:Player {
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    int flying_tick;
    State state_;
};

struct Map:Object {
    int layers_count;
    double ring_radius;
};

struct Obstruction:Object {

};

//конец блока формирования получения сообщения

//класс для отправки и получения
class actionServer {

private:
    Point myPosition;
    Vector mySight;

public:
    void getActionKey(std::string);
    void getActionMousePos(int, int);

    void sendActionMove(Direction);
    void sendActionBlink();
    void updatePosition();
    void updateSight(int, int);

    Object getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
