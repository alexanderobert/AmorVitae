//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#include "PacketManager.h"

std::string PacketManager::packet_handle_server(std::map<int, std::shared_ptr<Object>>& object) {
  /*  Object::Type type = object.type;

    if(type == Object::Type::PLAYER_OBJECT) {
        std::shared_ptr<Object> sh;
        auto ptr = std::static_pointer_cast<Player>(sh);

        ptree root;
        root.put("type", "player");
        root.put("speed", ptr->speed);
        root.put("x", ptr->position.x);
        root.put("y", ptr->position.y);

        std::stringstream buf;
        write_json (buf, root);
        return buf.str();
    }*/

}

struct ObjectInterface PacketManager::packet_adaptation_client(ptree& root) {
   /* struct MessageFromServe mes;
    if (root.get("type", "") == "player") {
        mes.typeOfObject = typeOfObject.player;
        mes.object.position.x = root.get("x", 0);
        mes.object.position.y = root.get("y", 0);
        mes.object.player.speed = root.get("speed", 0);
    }
    return mes;*/
}

std::string PacketManager::packet_handle_client(std::shared_ptr<ObjectInterface> event) {

}

Message PacketManager::packet_adaptation_server(ptree& root) {

}