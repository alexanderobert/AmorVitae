#ifndef AMORVITAE_COLLISIONMANAGER_H
#define AMORVITAE_COLLISIONMANAGER_H

#include <vector>
#include <Object.h>

class CollisionManager {
public:
    CollisionManager() = default;
    std::vector<std::shared_ptr<Object>>check_object_collisions(const std::map<int, std::shared_ptr<Object>>& objects,
                                                                std::shared_ptr<Object> object);
    bool is_object_collided(const std::map<int, std::shared_ptr<Object>>& objects,
                             std::shared_ptr<Object> object) const;
    void resolve_collision(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj);
private:
    bool is_collided(std::shared_ptr<Object> lhs_obj, std::shared_ptr<Object> rhs_obj);
    void resolve_collision(std::shared_ptr<Player> player, std::shared_ptr<Obstruction> obstruct) {
        player->position = player->position -  player->sight * player->speed;
    }

    /*
Calculate(Snaryad, Kamen);
Calculate(Player, Kamen);
Calculate(Snaryad, Player);

*/
};

#endif //AMORVITAE_COLLISIONMANAGER_H
