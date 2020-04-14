//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_PACKETMANAGER_H
#define NEW_PACKETMANAGER_H


struct Message {
    int ID_user;
    string type_event;
    json parametrs_event;
};



class PacketManager {
public:
    PacketManager();
    ~PacketManager();
    sf::Packet packet_handle(Object object);
    Message packet_adaptation(sf::Packet& packet);

private:
    sf::Packet packet;
    Object object
};


#endif //NEW_PACKETMANAGER_H
