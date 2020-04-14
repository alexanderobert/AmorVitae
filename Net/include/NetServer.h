//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_NETSERVER_H
#define NEW_NETSERVER_H

struct Message {
    int ID_user;
    string type_event;
    json parametrs_event;
};


class NetServer {
public:
    NetServer(int port);
    ~NetServer();

    Message accept_users(int player_count);

    void notify_all_users(Object object);

    Message get_client_actions();

private:
    int port;
    PacketManager packet_manager;
    Object object;

};


#endif //NEW_NETSERVER_H
