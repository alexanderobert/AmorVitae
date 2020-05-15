//
// Created by moira-q on 14.04.20.
//

#include <Event.h>
#include <include/Event.h>

std::shared_ptr<Object> Blink::proccess(std::shared_ptr<Object> obj, ObjectManager &objectmanager)  {
    Player player = *std::static_pointer_cast<Player>(obj).get();
    player.sight = player.normalize(sight);
    player.position = player.position + player.sight * BLINK_RANGE;
    return std::make_shared<Player>(player);
}

std::shared_ptr<Object> Move::proccess(std::shared_ptr<Object> obj, ObjectManager &objectmanager) {
    Player player = *std::static_pointer_cast<Player>(obj).get();

    switch (direction) {
        case UP: {
            player.position.y += player.speed;
            break;
        }
        case DOWN:{
            player.position.y -= player.speed;
            break;
        }
        case LEFT:{
            player.position.x -= player.speed;
            break;
        }
        case RIGHT:{
            player.position.y += player.speed;
            break;
        }
        default:
            break;
    }
    return std::make_shared<Player>(player);
    //obj.get()->position.;
}

std::shared_ptr<Object> Shot::proccess(std::shared_ptr<Object> obj, ObjectManager &objectmanager) {
    Player player = *std::static_pointer_cast<Player>(obj).get();
    player.sight = player.normalize(sight);
    Point bullet_postiton = player.position + Point(player.model.width, player.model.height);
    objectmanager.update_objects(std::make_shared<Bullet>(objectmanager.pick_enable_id(),
                                                          bullet_postiton, player.sight, player.ID));
    return std::make_shared<Player>(player);
}
