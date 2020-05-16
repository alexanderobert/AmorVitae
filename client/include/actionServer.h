#ifndef CLIENT_ACTIONSERVER_H
#define CLIENT_ACTIONSERVER_H

#include <memory>
#include <map>
#include <cmath>

#include <ifaddrs.h>
#include <cstring>

#include <iostream>

#include <vector>

const static int DEFAULT_BULLET_SPEED = 10;
const static int DEFAULT_PLAYER_SPEED = 5;

struct PointInterface {
    double x, y;
    PointInterface(double xpos, double ypos): x(xpos), y(ypos) {}
};

struct VectorInterface {
    PointInterface from, to;
    VectorInterface(PointInterface f, PointInterface t):from(f), to(t){}
};

struct ModelInterface {
    int height, width;
    ModelInterface(int h, int w):height(h), width(w) {}
};

enum DirectionInterface {
    up,
    down,
    left,
    right
};

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
    VectorInterface sight;
    EventInterface(EventType t, VectorInterface s): type(t), sight(s) {}
};

struct MoveInterface: EventInterface{
    DirectionInterface direction;
    MoveInterface(EventType t, VectorInterface s, DirectionInterface dir):EventInterface(t, s), direction(dir) {}
};

struct BlinkInterface: EventInterface{
    BlinkInterface(EventType t, VectorInterface s):EventInterface(t, s) {}
};

enum Type {
    STATIC_OBJECT,
    PLAYER_OBJECT,
    BULLET_OBJECT,
    MAP_OBJECT
};

//Объект получаемый от сервера
struct ObjectInterface {
    enum Type {
        STATIC_OBJECT,
        PLAYER_OBJECT,
        BULLET_OBJECT,
        MAP_OBJECT
    };
    PointInterface position;
    ModelInterface model;
    Type type;
    int ID;
    ObjectInterface(Type t, int id, PointInterface pos, ModelInterface mod):type(t), ID(id), position(pos), model(mod) {}

};

struct PlayerInterface:ObjectInterface {
    VectorInterface sight;
    int speed;
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    State state_;
    PlayerInterface(Type t, int id, PointInterface pos, ModelInterface mod): ObjectInterface(t, id, pos, mod),
                                                            sight({1,1}, {0,0}), speed(50) {}

};


struct MapInterface:ObjectInterface {
    int layers_count;
    double ring_radius;
    std::map<int, int> players_pts;
};

struct ObstructionInterface:ObjectInterface {
    ObstructionInterface(Type t, int id, PointInterface pos, ModelInterface mod): ObjectInterface(t, id, pos, mod) {}
};


struct BulletStateInterface {
    enum State {
        ACTIVE,
        INACTIVE
    };
    BulletStateInterface(): state_(State::ACTIVE), live_tick(0) {};
    int live_tick;
    State state_;
};

struct BulletInterface:ObjectInterface {

    BulletInterface(int id, PointInterface pos, PointInterface sight, int iniciator_id): ObjectInterface(Type::BULLET_OBJECT, id, pos, ModelInterface(15,15)),
                                                              sight(sight), speed(DEFAULT_BULLET_SPEED), iniciator_ID(iniciator_id) {};
    BulletStateInterface state;
    PointInterface sight;
    int iniciator_ID;
    int speed;
};
//конец блока формирования получения сообщения

//класс для отправки и получения
class actionServer {

private:
    PointInterface myPosition;
    VectorInterface mySight;

public:
    actionServer() : myPosition(0,0), mySight({0, 0}, {0, 0}) {};
    ~actionServer() = default;

    void sendActionMove(DirectionInterface);
    void sendActionBlink();
    void updatePosition();
    void updateSight(int, int);

    std::vector<std::shared_ptr<ObjectInterface>> getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
