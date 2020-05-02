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
    ObjectManager() = default; // захватываем мьютекс перед обновление базы
    void update_objects(const Object& changed_objects);
    std::shared_ptr<Object> get_object_by_id(int id);
    std::map<int, std::shared_ptr<Object>>& get_objects_by_map() const;


private:
    std::map<int, std::shared_ptr<Object>> objects;
    std::mutex m;

};


#endif //AVM_OBJECT_MANAGER_H
