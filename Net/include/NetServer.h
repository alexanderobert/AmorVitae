//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_NETSERVER_H
#define NEW_NETSERVER_H
#include <boost/asio.hpp>
#include <User.h>
#include <vector>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <Object.h>
#include <message_server.h>
#include <PacketManager.h>




class NetServer {
public:
    explicit NetServer(int port) {}
    ~NetServer() = default;

    std::vector<User> accept_users(int player_count);

    void notify_all_users(std::map<int, std::shared_ptr<Object>>&);

    Message get_client_action(User& user);

private:
    int port{};
    std::vector<User> users;
    boost::asio::io_service io_service;
    PacketManager packet_manager;
    PacketManager qwe;
};


#endif //NEW_NETSERVER_H
