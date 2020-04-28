//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_EVENT_H
#define AVM_EVENT_H


#include "Object.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Event {
public:
    Event() = default;
    virtual Object& proccess(Object& obj);
    virtual ~Event() = 0;
    int IniciatorID;
};

class Move: public Event {
public:

    Move(std::shared_ptr<Player> object, Direction direction);
    Object& proccess(Object& obj) override;

};

class Blink: public Event {
public:

    Blink(std::shared_ptr<Player> object, Direction direction);
    Object& proccess(Object& obj) override;

};


#endif //AVM_EVENT_H
