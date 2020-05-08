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
    EventInterface(EventType t, Vector s): type(t), sight(s) {}
};

struct MoveInterface: EventInterface{
    Direction direction;
    MoveInterface(EventType t, Vector s, Direction dir):EventInterface(t, s), direction(dir) {}
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
    ObjectInterface(Type t, int id, Point pos, Model mod):type(t), ID(id), position(pos), model(mod) {}

};

struct PlayerInterface:ObjectInterface {
    Vector sight;
    int speed;
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    State state_;
    PlayerInterface(Type t, int id, Point pos, Model mod): ObjectInterface(t, id, pos, mod),
                                                            sight({1,1}, {0,0}), speed(50) {}

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

    std::shared_ptr<ObjectInterface> getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
