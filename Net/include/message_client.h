//
// Взял у клиента
//

#ifndef AMORVITAE_MESSAGE_CLIENT_H
#define AMORVITAE_MESSAGE_CLIENT_H

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

#endif //AMORVITAE_MESSAGE_CLIENT_H
