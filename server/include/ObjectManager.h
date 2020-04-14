//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_MANAGER_H
#define AVM_OBJECT_MANAGER_H


#include <map>
#include <vector>
#include "Object.h"

class ObjectManager {
public:
    ObjectManager() = default;
    void update_objects(std::vector<Object> changed_objects);
    Object get_object_by_id(int id);
    const std::map<int, Object>& get_objects();


private:
    std::map<int, Object> objects;

};


#endif //AVM_OBJECT_MANAGER_H
