//
// Created by moira-q on 24.04.20.
//

#ifndef AMORVITAE_PACKETMANAGER_H
#define AMORVITAE_PACKETMANAGER_H

#include <string>

struct Message {
    int ID_user;
    std::string type_event;
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

#endif //AMORVITAE_PACKETMANAGER_H
