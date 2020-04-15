//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_NETCLIENT_H
#define NEW_NETCLIENT_H
#include <PacketManager.h>


class NetClient {
public:
    NetClient();
    ~NetClient();

    bool connect_to_server(string addr_server);
    void send_user_action(Object object);
    Message get_server_message();

private:
    bool send_packet(sf::Packet& packet);
    bool status;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket sock(io_service);
    PacketManager packet_manager;
    Object object
};

#endif //NEW_NETCLIENT_H
