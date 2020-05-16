#ifndef CLIENT_CLIENTCONNECTION_H
#define CLIENT_CLIENTCONNECTION_H

#include <ifaddrs.h>
#include <cstring>

#include <iostream>

#include <NetClient.h>

class clientConnection{
private:
    std::string addr_server;

public:

    int myId;

//    void checkHostName(int hostname);
//    void checkHostEntry(struct hostent * hostentry);
//    void checkIPbuffer(char *IPbuffer);
//    void getIP();
//    std::string getIPAddress();

    int connectClient(NetClient &);
    void closeConnectClient();
};



#endif //CLIENT_CLIENTCONNECTION_H
