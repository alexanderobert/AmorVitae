//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_EVENT_H
#define AVM_EVENT_H


#include "Object.h"

class Event {
public:
    Event() = default;
    virtual void set_fields(IniciatorID, parametrs) = 0;
    virtual void proccess(Object obj);
    virtual ~Event() = 0;
    int IniciatorID;
};


#endif //AVM_EVENT_H
