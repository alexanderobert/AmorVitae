//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_NETSERVER_H
#define NEW_NETSERVER_H
#include <PacketManager.h>


class NetServer {
public:
    NetServer(int port);
    ~NetServer();

    Users accept_users(int player_count);

    void notify_all_users(Object object);

    Message get_client_action(User);

private:
    int port;
    PacketManager packet_manager;
    Object object;
};


#endif //NEW_NETSERVER_H
