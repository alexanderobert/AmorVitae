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
#include <PacketManagerServer.h>




class NetServer {
public:
    explicit NetServer(int port) {}
    ~NetServer() = default;

    std::vector<User> accept_users(int player_count, const ObjectManager& objm);

    void notify_all_users(std::unordered_map<int, std::shared_ptr<Object>>&);

    std::shared_ptr<Event> get_client_action(User& user);

    int do_read_header(User&);

private:
    int port{};
    std::vector<User> users;
    boost::asio::io_service io_service;
    PacketManagerServer packet_manager;
    //PacketManager qwe;
};


#endif //NEW_NETSERVER_H
