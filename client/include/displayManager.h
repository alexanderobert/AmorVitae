#ifndef CLIENT_DISPLAYMANAGER_H
#define CLIENT_DISPLAYMANAGER_H

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

#include "json.hpp"

using json = nlohmann::json;

class displayManager {

public:
    void playerDataToGraph(json);
    void projectFileDataToGraph(json);
    void mapCodeToGraph(json);
    void configToGraph(json);
};

#endif //CLIENT_DISPLAYMANAGER_H
