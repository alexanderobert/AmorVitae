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

struct EventInterface {
    EventType type; //move, blink
    Vector sight;
};

struct Move: EventInterface{
    Direction direction;
};

struct Blink: EventInterface{

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
struct ObjectInterface {

    Point position;
    Model model;
    Type type;
    int ID;
};

struct Player:ObjectInterface {
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

struct Map:ObjectInterface {
    int layers_count;
    double ring_radius;
};

struct Obstruction:ObjectInterface {

};

//конец блока формирования получения сообщения

//класс для отправки и получения
class actionServerInterface {

private:
    Point myPosition;
    Vector mySight;

public:

    void sendActionMove(Direction);
    void sendActionBlink();
    void updatePosition();
    void updateSight(int, int);

    ObjectInterface getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
