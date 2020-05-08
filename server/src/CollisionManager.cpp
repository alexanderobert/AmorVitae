//
// Created by moira-q on 07.05.20.
//

#include <CollisionManager.h>

std::vector<std::shared_ptr<Object>>
CollisionManager::check_object_collisions(const std::map<int, std::shared_ptr<Object>> &objects,
                                          std::shared_ptr<Object> object) {
}

bool CollisionManager::is_object_collided(const std::map<int, std::shared_ptr<Object>> &objects,
                                          std::shared_ptr<Object> object) const {
    return false;
}

void CollisionManager::resolve_collision(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj) {

}

bool CollisionManager::is_collided(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj) {

}

