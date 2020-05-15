//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_EVENT_H
#define AVM_EVENT_H

#include <Object.h>
#include <ObjectManager.h>

const static int BLINK_RANGE = 1000;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Event {
public:
    Event(int Player_ID, Vector sight_direct):IniciatorID(Player_ID), sight(sight_direct) {};
    virtual std::shared_ptr<Object> proccess(std::shared_ptr<Object>, ObjectManager& objectmanager) = 0;
    int IniciatorID;
    Vector sight;
};

class Move: public Event {
public:
    Move(int Player_ID, Vector sight_direct, Direction dir): Event(Player_ID, sight_direct), direction(dir) {}
    std::shared_ptr<Object> proccess(std::shared_ptr<Object> obj, ObjectManager& objectmanager) override;
    Direction direction;

};

class Blink: public Event {
public:
    Blink(int Player_ID, Vector sight_direct): Event(Player_ID, sight_direct) {};
    std::shared_ptr<Object> proccess(std::shared_ptr<Object> obj, ObjectManager& objectmanager) override;
};

class Shot: public Event {
public:
    Shot(int Iniciator_ID, Vector sight_direct): Event(Iniciator_ID, sight_direct) {};
    std::shared_ptr<Object> proccess(std::shared_ptr<Object> obj, ObjectManager& objectmanager) override;
};

#endif //AVM_EVENT_H