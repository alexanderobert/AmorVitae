//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#include <iostream>
#include "PacketManager.h"

std::vector<std::shared_ptr<ObjectInterface>> PacketManager::packet_adaptation_client(ptree& root) {
    std::map <std::string, int> mp;
    mp["player"] = 1;
    mp["bullet"] = 2;
    mp["map"] = 3;
    mp["static"] = 4;
    std::vector<std::shared_ptr<ObjectInterface>> vector;

    for (int j = 0; j < root.get("object", 0); ++j) {
        ptree tree = root.get_child(std::to_string(j));
        switch (mp[tree.get("type", "")]) {
            case 1: {
                int id = tree.get("id", 0);
                std::string x = tree.get("x", "");
                std::string y = tree.get("y", "");
                struct PlayerInterface pl(ObjectInterface::Type::PLAYER_OBJECT, id, {
                    (stod(x)),
                            (stod(y))},
                {15, 15});
                std::shared_ptr<ObjectInterface> ptr = std::make_shared<PlayerInterface>(pl);
                vector.push_back(ptr);
                break;
            }

            case 2: {
                std::string x = tree.get("x", "");
                std::string y = tree.get("y", "");
                std::string sight_x = tree.get("sight.x", "");
                std::string sight_y = tree.get("sight.y", "");
                struct BulletInterface bi(0, {stod(x), stod(y)},
                        {stod(sight_x), stod(sight_x)}, 0);
                std::shared_ptr<ObjectInterface> ptr = std::make_shared<BulletInterface>(bi);
                vector.push_back(ptr);
                break;
            }
            case 3: {
                std::map<int, int> pts_player;
                std::string layers_count = tree.get("layers_count", "");
                std::string ring_radius = tree.get("ring_radius", "");
                std::string count_player = tree.get("count_player", "");
                for (int k = 0; k < std::stoi(count_player); ++k) {
                    std::string pts = tree.get(std::to_string(k), "");
                    pts_player.insert({k, std::stoi(pts)});
                }
                auto a = std::stoi(layers_count);
                auto b = std::stod(ring_radius);
                struct MapInterface mi(1, a, b, pts_player);
                std::shared_ptr<ObjectInterface> ptr = std::make_shared<MapInterface>(mi);
                vector.push_back(ptr);

                break;
            }
            case 4: {
                break;
            }

            default: {
                break;
            }

        }
    }
    return vector;
}

std::string PacketManager::packet_handle_client(std::shared_ptr<EventInterface>& event) {
    std::map <EventInterface::EventType, int> mp;
    mp[EventInterface::move] = 1;
    mp[EventInterface::blink] = 2;
    mp[EventInterface::shot] = 3;

    ptree root;
    switch (mp[event->type]) {
        case 1: {
            auto ptr = std::static_pointer_cast<MoveInterface>(event);
            root.put("type", "move");
            root.put("direction", ptr->direction);
            root.put("sight.from.x", ptr->sight.from.x);
            root.put("sight.from.y", ptr->sight.from.y);
            root.put("sight.to.x", ptr->sight.to.x);
            root.put("sight.to.y", ptr->sight.to.y);

            break;
        }
        case 2: {
            auto ptr = std::static_pointer_cast<BlinkInterface>(event);
            root.put("type", "blink");
            root.put("sight.from.x", ptr->sight.from.x);
            root.put("sight.from.y", ptr->sight.from.y);
            root.put("sight.to.x", ptr->sight.to.x);
            root.put("sight.to.y", ptr->sight.to.y);
            break;
        }
        case 3: {
            auto ptr = std::static_pointer_cast<ShotInterface>(event);
            root.put("type", "shot");
            root.put("sight.from.x", ptr->sight.from.x);
            root.put("sight.from.y", ptr->sight.from.y);
            root.put("sight.to.x", ptr->sight.to.x);
            root.put("sight.to.y", ptr->sight.to.y);
            break;
        }
        default: {
            break;
        }

    }
    std::stringstream buf;
    write_json(buf, root);
    return buf.str();
}