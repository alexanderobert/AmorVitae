//
// Created by moira-q on 14.04.20.
//

#include <ObjectManager.h>

#include <include/ObjectManager.h>


int ObjectManager::pick_enable_id() const{
    std::lock_guard<std::mutex>lg(id_cointer_m);
    int result = id_counter;
    id_counter++;
    return result;
}

std::unordered_map<int, std::shared_ptr<Object>> &ObjectManager::get_objects_by_map() {
    return objects;
}

std::shared_ptr<Object> &ObjectManager::get_object_by_id(int id) {
    return objects[id];
}

void ObjectManager::update_objects(std::shared_ptr<Object> changed_object) {
    objects[changed_object->ID] = changed_object;
}
