//
// Created by Vladislav Shushpanov on 13.05.2020.
//

#ifndef AMORVITAE_PACKETMANAGERSERVER_H
#define AMORVITAE_PACKETMANAGERSERVER_H

#include <string>
#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <message_client.h>
#include <message_server.h>
#include <Event.h>
#include <Object.h>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class PacketManagerServer {
public:
    PacketManagerServer() = default;
    ~PacketManagerServer() = default;
    std::string packet_handle_server(std::unordered_map<int, std::shared_ptr<Object>>& object);
    std::shared_ptr<Event> packet_adaptation_server(ptree& root);
};


#endif //AMORVITAE_PACKETMANAGERSERVER_H