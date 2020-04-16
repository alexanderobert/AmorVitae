#ifndef SKELETON_CLIENTCONNECTION_H
#define SKELETON_CLIENTCONNECTION_H

class clientConnection {
public:
    clientConnection() = default;
    virtual ~clientConnection() = 0;

    bool connectClient(long, int);
    void closeConnectClient();
private:
    long ip;
    int port;
    struct message;
    bool statusOfConnection;
};

#endif //SKELETON_CLIENTCONNECTION_H
