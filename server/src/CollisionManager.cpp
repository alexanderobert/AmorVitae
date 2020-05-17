//
// Created by moira-q on 07.05.20.
//

#include <CollisionManager.h>
#include <include/CollisionManager.h>


std::vector<std::shared_ptr<Object>>
CollisionManager::check_object_collisions(const std::map<int, std::shared_ptr<Object>> &objects,
                                          std::shared_ptr<Object> object) {
    std::vector<std::shared_ptr<Object>> result;
    for (auto& obj: objects) {
        if (is_collided(obj.second, object)) {
            if (obj.second->ID != object->ID) {
                result.push_back(obj.second);
            }
        }
    }
    return result;
}

bool CollisionManager::is_object_collided(const std::map<int, std::shared_ptr<Object>> &objects,
                                          std::shared_ptr<Object> object) const {
    for (auto& obj: objects) {
        if (is_collided(obj.second, object)) {
            if (obj.second->ID != object->ID) {
                return true;
            }
        }
    }
    return false;
}

void CollisionManager::resolve_collision(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj) {
    if (lhs_obj->type == Object::PLAYER_OBJECT) {
        std::shared_ptr<Player> lplayer = std::static_pointer_cast<Player>(lhs_obj);
        if (rhs_obj->type == Object::PLAYER_OBJECT) {
            std::shared_ptr<Player> rplayer = std::static_pointer_cast<Player>(rhs_obj);
            resolve_collision(lplayer, rplayer);
        } else if (lhs_obj->type == Object::BULLET_OBJECT) {
            std::shared_ptr<Bullet> rbullet = std::static_pointer_cast<Bullet>(rhs_obj);
            resolve_collision(lplayer, rbullet);
        } else if (lhs_obj->type == Object::STATIC_OBJECT) {
            std::shared_ptr<Obstruction> robstruction = std::static_pointer_cast<Obstruction>(rhs_obj);
            resolve_collision(lplayer, robstruction);
        }
    } else if (lhs_obj->type == Object::BULLET_OBJECT) {
        std::shared_ptr<Bullet> lbullet = std::static_pointer_cast<Bullet>(lhs_obj);
        if (rhs_obj->type == Object::PLAYER_OBJECT) {
            std::shared_ptr<Player> rplayer = std::static_pointer_cast<Player>(rhs_obj);
            resolve_collision(lbullet, rplayer);
        } else if (lhs_obj->type == Object::BULLET_OBJECT) {
            std::shared_ptr<Bullet> rbullet = std::static_pointer_cast<Bullet>(rhs_obj);
            resolve_collision(lbullet, rbullet);
        } else if (lhs_obj->type == Object::STATIC_OBJECT) {
            std::shared_ptr<Obstruction> robstruction = std::static_pointer_cast<Obstruction>(rhs_obj);
            resolve_collision(lbullet, robstruction);
        }
    } else if (lhs_obj->type == Object::STATIC_OBJECT) {
        std::shared_ptr<Obstruction> lobstruction = std::static_pointer_cast<Obstruction>(lhs_obj);
        if (rhs_obj->type == Object::PLAYER_OBJECT) {
            std::shared_ptr<Player> rplayer = std::static_pointer_cast<Player>(rhs_obj);
            resolve_collision(lobstruction, rplayer);
        } else if (lhs_obj->type == Object::BULLET_OBJECT) {
            std::shared_ptr<Bullet> rbullet = std::static_pointer_cast<Bullet>(rhs_obj);
            resolve_collision(lobstruction, rbullet);
        } else if (lhs_obj->type == Object::STATIC_OBJECT) {
            std::shared_ptr<Obstruction> robstruction = std::static_pointer_cast<Obstruction>(rhs_obj);
            resolve_collision(lobstruction, robstruction);
        }
    }
}

bool CollisionManager::is_collided(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj) const {
    return !((lhs_obj->position.y + lhs_obj->model.height) < (rhs_obj->position.y) ||
             (lhs_obj->position.y) > (rhs_obj->position.y + rhs_obj->model.height) ||
             (lhs_obj->position.x + lhs_obj->model.width) < (rhs_obj->position.x) ||
             (lhs_obj->position.x) > (rhs_obj->position.x + rhs_obj->model.width));
}

void CollisionManager::resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Obstruction> obstruct)  {
    player->position = player->position -  player->sight * player->speed;
}

void CollisionManager::resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Bullet> bullet) {

    if ((bullet->state.get_state() == BulletState::ACTIVE) && (player->ID != bullet->iniciator_ID)) {//LOVUSHKA
        player->state_.state_to_fly();
        player->sight = bullet->sight;
        player->speed = bullet->speed;
        bullet->state.state_to_inactive();
    }
}

void CollisionManager::resolve_collision(std::shared_ptr<Bullet> bullet, std::shared_ptr<Obstruction> obstruct) {
    bullet->state.state_to_inactive();
}

void CollisionManager::resolve_collision(std::shared_ptr<Obstruction> obstruct, std::shared_ptr<Player> player) {
    resolve_collision(player, obstruct);

}

void CollisionManager::resolve_collision(std::shared_ptr<Bullet> bullet, std::shared_ptr<Player> player) {
    resolve_collision(player, bullet);

}

void CollisionManager::resolve_collision(std::shared_ptr<Obstruction> obstruct, std::shared_ptr<Bullet> bullet) {
    resolve_collision(bullet, obstruct);

}