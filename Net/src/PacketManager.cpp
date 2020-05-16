//
// Created by Vladislav Shushpanov on 14.04.2020.
//

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
