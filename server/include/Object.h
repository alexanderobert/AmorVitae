//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H


class Object {
public:
    Object() = default;
    virtual ~Object() = 0;
private:
    int ID;
};


#endif //AVM_OBJECT_H
