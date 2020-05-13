#ifndef CLIENT_DISPLAYMANAGER_H
#define CLIENT_DISPLAYMANAGER_H

#include "actionServer.h"

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

class displayManager {

private:
    PointInterface position;
    VectorInterface sight;

public:
    void playerDataToGraph(struct ObjectInterface);
    void projectFileDataToGraph(struct ObjectInterface);
    void mapCodeToGraph(struct ObjectInterface);
    void configToGraph(struct ObjectInterface);
};

#endif //CLIENT_DISPLAYMANAGER_H
