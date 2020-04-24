//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_EVENT_H
#define AVM_EVENT_H


#include "Object.h"

class Event {
public:
    Event() = default;
    virtual Object& proccess(Object& obj);
    virtual ~Event() = 0;
    int IniciatorID;
};

class Move: public Event {
public:
    Move(int inic_id, int speed, Direction direction);
    Object& proccess(Object& obj) override;

};


#endif //AVM_EVENT_H
