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
    virtual Object proccess(std::shared_ptr<Object>);
    virtual ~Event() = 0;
    int IniciatorID;
};

class Move: public Event {
public:
    Move(int Player_ID, Direction dir):direction(dir) {}
    Object proccess(std::shared_ptr<Object> obj) override {
        switch (direction) {
            case UP:
            case DOWN:
            case LEFT:
            case RIGHT:
                break;
        }
        //obj.get()->position.;
    }
    Direction direction;

};

class Blink: public Event {
public:

    Blink(int Player_ID);
    Object proccess(std::shared_ptr<Object> obj) override {

    }
};

#endif //AVM_EVENT_H