//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_NETCLIENT_H
#define NEW_NETCLIENT_H
#include <PacketManager.h>
#include <string>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <boost/asio/use_awaitable.hpp>

class NetClient {

public:
    NetClient() = default;
    ~NetClient() = default;

    void connect_to_server(std::string addr_server, int port);
    void send_user_action(std::shared_ptr<EventInterface>& event);
    std::vector<std::shared_ptr<ObjectInterface>> get_server_message();
    void do_write_header(int size);

private:
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

    //bool send_packet(sf::Packet& packet);
    //  void send(Object& object, socket_ptr sock);
    boost::asio::io_service io_service;
    PacketManager packet_manager;
};

#endif //NEW_NETCLIENT_H