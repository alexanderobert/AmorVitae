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

#include <Object.h>
#include <Event.h>

//блок формирования сообщения для отправки



struct MousePosition {
    int x;
    int y;
};


struct EventInterface {
    enum EventType {
        move,
        blink
    };
    EventType type; //move, blink
    Vector sight;
};

struct MoveInterface: EventInterface{
    Direction direction;
};

struct BlinkInterface: EventInterface{

};


//Объект получаемый от сервера
struct ObjectInterface {
    enum Type {
        STATIC_OBJECT,
        PLAYER_OBJECT,
        BULLET_OBJECT,
        MAP_OBJECT
    };
    Point position;
    Model model;
    Type type;
    int ID;
};

struct PlayerInterface:ObjectInterface {
    Vector sight;
    int speed;
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    State state_;

};


struct MapInterface:ObjectInterface {
    int layers_count;
    double ring_radius;
    std::map<int, int> players_pts;
};

struct ObstructionInterface:ObjectInterface {

};

//конец блока формирования получения сообщения

//класс для отправки и получения
class actionServerInterface {

private:
    Point myPosition;
    Vector mySight;

public:
    actionServerInterface() : myPosition(0,0), mySight({0, 0}, {0, 0}) {};
    ~actionServerInterface() = default;

    void sendActionMove(Direction);
    void sendActionBlink();
    void updatePosition();
    void updateSight(int, int);

    ObjectInterface getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
