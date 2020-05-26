//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_MANAGER_H
#define AVM_OBJECT_MANAGER_H


#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <Object.h>
#include <unordered_map>
#include <CollisionManager.h>

class ObjectManager {
public:
    ObjectManager():id_counter(0) {};
    void update_objects(std::shared_ptr<Object> changed_object) {
        objects[changed_object->ID] = changed_object;
    }
    std::shared_ptr<Object>& get_object_by_id(int id) {
        return objects[id];
    }
    std::unordered_map<int, std::shared_ptr<Object>>& get_objects_by_map() {
        return objects;
    }
    int pick_enable_id() const  {
        std::lock_guard<std::mutex>lg(id_cointer_m);
        int result = id_counter;
        id_counter++;
        return result;
    }
    CollisionManager collisionSolver;
private:

    mutable int id_counter;
    mutable std::mutex id_cointer_m;
    std::unordered_map<int, std::shared_ptr<Object>> objects;
};


#endif //AVM_OBJECT_MANAGER_H