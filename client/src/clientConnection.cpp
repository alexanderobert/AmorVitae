#include "clientConnection.h"

struct IPv4 {
    unsigned char b1, b2, b3, b4;
};

void clientConnection::checkHostName(int hostname){
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

void clientConnection::checkHostEntry(struct hostent * hostentry){
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}

void clientConnection::checkIPbuffer(char *IPbuffer){
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}

void clientConnection::getIP(){
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;

    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
    IPbuffer = inet_ntoa(*((struct in_addr*)
            host_entry->h_addr_list[0]));

    printf("Hostname: %s\n", hostbuffer);
    printf("Host IP: %s", IPbuffer);
}

std::string clientConnection::getIPAddress(){
    std::string ipAddress="Unable to get IP Address";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    success = getifaddrs(&interfaces);
    if (success == 0) {
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                if(strcmp(temp_addr->ifa_name, "en0")==0){
                    ipAddress=inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr);
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    freeifaddrs(interfaces);
    return ipAddress;
}

bool clientConnection::connectClient(){
    //return bool connect_to_server(std::string addr_server); from NetClient
    return true;
}

void clientConnection::closeConnectClient(){
    //функция разрыва соединения
}

json clientConnection::getServer(){
    // get_server_action(); from NetClient
    json pass;
    pass["key"] = "test";

    return pass;
}