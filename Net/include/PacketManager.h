//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_PACKETMANAGER_H
#define NEW_PACKETMANAGER_H

#include <string>
#include <Object.h>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <message_client.h>
#include <message_server.h>
#include <actionServer.h>


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


class PacketManager {
public:
    PacketManager() = default;
    ~PacketManager() = default;
    std::string packet_handle_server(std::map<int, std::shared_ptr<Object>>& object);
    std::string packet_handle_client(std::shared_ptr<EventInterface>& event);
    std::shared_ptr<Event> packet_adaptation_server(ptree& root);
    std::vector<std::shared_ptr<ObjectInterface>> packet_adaptation_client(ptree& root);

};


#endif //NEW_PACKETMANAGER_H
