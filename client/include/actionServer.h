#ifndef CLIENT_ACTIONSERVER_H
#define CLIENT_ACTIONSERVER_H

#include <memory>
#include <map>
#include <cmath>

#include <ifaddrs.h>
#include <cstring>

#include <iostream>

#include <vector>

#include <NetClient.h>


//класс для отправки и получения
class actionServer {

private:
    NetClient network;

    std::string addr_server = "127.0.0.1";
    int port = 8001;

public:
    actionServer();
    ~actionServer() = default;

    PointInterface myPosition;
    VectorInterface mySight;

    int myId;

    void connectClient();
    void closeConnectClient();

    void sendActionMove(DirectionInterface);
    void sendActionBlink();
    void sendActionShot();
    void updatePosition(const std::vector<std::shared_ptr<ObjectInterface>> &);
    void updateSight(double, double);

    std::vector<std::shared_ptr<ObjectInterface>> getMessage();
};

#endif //CLIENT_ACTIONSERVER_H
