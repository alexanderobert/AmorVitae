//
// Created by Vladislav Shushpanov on 13.05.2020.
//
#include <PacketManagerServer.h>

std::string PacketManagerServer::packet_handle_server(std::map<int, std::shared_ptr<Object>>& object) {
    std::map <Object::Type, int> mp;
    mp[Object::Type::PLAYER_OBJECT] = 1;
    mp[Object::Type::BULLET_OBJECT] = 2;
    mp[Object::Type::MAP_OBJECT] = 3;
    mp[Object::Type::STATIC_OBJECT] = 4;

    ptree root;
    root.put("object", object.size());
    for (int j = 0; j < object.size(); ++j) {
        ptree tree;
        switch (mp[object[j]->type]) {
            case 1: {
                auto ptr = std::static_pointer_cast<Player>(object[j]);
                tree.put("type", "player");
                tree.put("id", ptr->ID);
                tree.put("x", ptr->position.x);
                tree.put("y", ptr->position.y);
                root.add_child(std::to_string(j), tree);
                break;
            }
            case 2: {
                auto ptr = std::static_pointer_cast<Bullet>(object[j]);
                    tree.put("type", "bullet");
                    tree.put("x", ptr->position.x);
                    tree.put("y", ptr->position.y);
                    root.add_child(std::to_string(j), tree);
                break;

            }
            case 3: {
                auto ptr = std::static_pointer_cast<Map>(object[j]);
                tree.put("type", "map");
                tree.put("layers_count", ptr->layers_count);
                tree.put("ring_radius", ptr->ring_radius);
                tree.put("count_player", ptr->players_pts.size());
                for (const auto& item : ptr->players_pts) {
                    tree.put(std::to_string(item.first), item.second);
                }
                root.add_child(std::to_string(j), tree);
                break;
            }
            case 4: {
                auto ptr = std::static_pointer_cast<Obstruction>(object[j]);
                tree.put("type", "static");
                tree.put("x", ptr->position.x);
                tree.put("y", ptr->position.y);
                tree.put("model.width", ptr->model.width);
                tree.put("model.height", ptr->model.height);
                root.add_child(std::to_string(j), tree);
                break;
            }

            default: {
                break;
            }

        }
    }
    std::stringstream buf;
    write_json(buf, root);
    return buf.str();
}

std::shared_ptr<Event> PacketManagerServer::packet_adaptation_server(ptree& root) {
    std::map <std::string, int> mp;
    mp["move"] = 1;
    mp["blink"] = 2;
    mp["shot"] = 3;


    std::map <std::string, Direction> dir;
    dir["1"] = Direction::DOWN;
    dir["2"] = Direction::LEFT;
    dir["3"] = Direction::RIGHT;
    dir["0"] = Direction::UP;
    std::shared_ptr<Event> ptr;
    switch (mp[root.get("type", "")]) {
        case 1: {
            int id = root.get("IDuser", 0);
            Direction direction = dir[root.get("direction", "")];
            double sight_from_x = root.get("sight.from.x", 0);
            double sight_from_y = root.get("sight.from.y", 0);
            double sight_to_x = root.get("sight.to.x", 0);
            double sight_to_y = root.get("sight.to.y", 0);
            auto move = Move(id, {{sight_from_x, sight_from_y}, {sight_to_x, sight_to_y}}, direction);
            ptr = std::make_shared<Move>(move);
            break;
        }
        case 2: {
            int id = root.get("IDuser", 0);
            double sight_from_x = root.get("sight.from.x", 0);
            double sight_from_y = root.get("sight.from.y", 0);
            double sight_to_x = root.get("sight.to.x", 0);
            double sight_to_y = root.get("sight.to.y", 0);
            auto blink = Blink(id, {{sight_from_x, sight_from_y}, {sight_to_x, sight_to_y}});
            ptr = std::make_shared<Blink>(blink);
            break;

        }
        case 3: {
            int id = root.get("IDuser", 0);
            double sight_from_x = root.get("sight.from.x", 0);
            double sight_from_y = root.get("sight.from.y", 0);
            double sight_to_x = root.get("sight.to.x", 0);
            double sight_to_y = root.get("sight.to.y", 0);
            auto shot = Shot(id, {{sight_from_x, sight_from_y}, {sight_to_x, sight_to_y}});
            ptr = std::make_shared<Shot>(shot);
            break;
        }
        default: {
            break;
        }

    }
    return ptr;



}