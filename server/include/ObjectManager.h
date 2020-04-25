//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_MANAGER_H
#define AVM_OBJECT_MANAGER_H


#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include "Object.h"

class ObjectManager {
public:
    ObjectManager() = default;
    void update_objects(const std::vector<Object>& changed_objects); // захватываем мьютекс перед обновление базы
    Object const* get_object_by_id(int id);
    const std::vector<Object>& get_objects_by_array() const;
    const std::map<int, Object>& get_objects_by_map() const;


private:
    std::map<int, Object> objects;
    std::mutex m;

};


#endif //AVM_OBJECT_MANAGER_H
