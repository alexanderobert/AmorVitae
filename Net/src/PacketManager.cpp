//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#include "PacketManager.h"

std::string PacketManager::packet_handle_server(std::map<int, std::shared_ptr<Object>>& object) {
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
                tree.put("model.height", ptr->model.height);
                tree.put("model.width", ptr->model.width);
                tree.put("sight.x", ptr->sight.x);
                tree.put("sight.y", ptr->sight.y);
                root.add_child(std::to_string(j), tree);
                break;

            }
            case 3: {
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
    std::stringstream buf;
    write_json(buf, root);
    return buf.str();
}

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
                double x = tree.get("x", 0);
                double y = tree.get("y", 0);
                struct PlayerInterface pl(ObjectInterface::Type::PLAYER_OBJECT, id, {x, y}, {30, 30});
                std::shared_ptr<ObjectInterface> ptr = std::make_shared<PlayerInterface>(pl);
                vector.push_back(ptr);
            }

            case 2: {
                //пуля есть только у сервера
                break;
            }
            case 3: {
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
        default: {
            break;
        }

    }
    std::stringstream buf;
    write_json(buf, root);
    return buf.str();
}


std::shared_ptr<Event> PacketManager::packet_adaptation_server(ptree& root) {
    std::map <std::string, int> mp;
    mp["move"] = 1;
    mp["blink"] = 2;

    std::map <std::string, Direction> dir;
    dir["DOWN"] = Direction::DOWN;
    dir["LEFT"] = Direction::LEFT;
    dir["RIGHT"] = Direction::RIGHT;
    dir["UP"] = Direction::UP;
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
        default: {
            break;
        }

    }
    return ptr;



}