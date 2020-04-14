//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_USER_H
#define NEW_USER_H

#include <sys/socket.h>
#include <boost/asio.hpp>



class User {
public:
    User(int ID_user, boost::asio::ip::tcp::socket sock(io_service));
    ~User();

    int get_username();

    void send_packet(Packet& packet);

    bool receive_packet(sf::Packet& packet);

private:
    int ID_user;
    bool status;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket sock(io_service);
};



#endif //NEW_USER_H
