#ifndef AMORVITAE_USER_H
#define AMORVITAE_USER_H
#include <sys/socket.h>

class User {
public:
    User(int ID_user, boost::asio::ip::tcp::socket sock(io_service));
    ~User();

    int get_username();

    void send_packet(sf::Packet& packet);

    bool receive_packet(sf::Packet& packet);

private:
    int ID_user;
    bool status;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket sock(io_service);
};

#endif //AMORVITAE_USER_H
