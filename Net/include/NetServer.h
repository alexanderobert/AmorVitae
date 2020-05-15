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
#include <message_server.h>
#include <PacketManagerServer.h>
#include <ObjectManager.h>
//#include <boost/asio/use_awaitable.hpp>

class NetServer {
public:
    explicit NetServer(int port) {}
    ~NetServer() = default;

    std::vector<User> accept_users(int players_count, const ObjectManager& objm);
    void notify_all_users(std::map<int, std::shared_ptr<Object>>&);
    std::shared_ptr<Event> get_client_action(User& user);
    int do_read_header(User& user);

private:
    int port{};
    std::vector<User> users;
    boost::asio::io_service io_service;
    PacketManagerServer packet_manager;
};


#endif //NEW_NETSERVER_H
