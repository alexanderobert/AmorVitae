//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_NETSERVER_H
#define NEW_NETSERVER_H
#include <PacketManager.h>
#include <boost/asio.hpp>
#include <User.h>
#include <vector>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <Object.h>
#include <message_client.h>



class NetServer {
public:
    explicit NetServer(int port) {}
    ~NetServer() = default;

    std::vector<User> accept_users(int player_count);

    void notify_all_users(Object& object);

    Message get_client_action(User& user);

private:
    int port{};
    std::vector<User> users;
    boost::asio::io_service io_service;
    PacketManager packet_manager;
};


#endif //NEW_NETSERVER_H
