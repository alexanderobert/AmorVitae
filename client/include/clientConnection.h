#ifndef CLIENT_CLIENTCONNECTION_H
#define CLIENT_CLIENTCONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ifaddrs.h>
#include <cstring>

#include <iostream>

class clientConnectionInterface {
private:
    std::string addr_server;

public:

    int myId;

    void checkHostName(int hostname);
    void checkHostEntry(struct hostent * hostentry);
    void checkIPbuffer(char *IPbuffer);
    void getIP();
    std::string getIPAddress();

    int connectClient();
    void closeConnectClient();
};



#endif //CLIENT_CLIENTCONNECTION_H
