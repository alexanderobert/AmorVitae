#ifndef SKELETON_CLIENTMANAGER_H
#define SKELETON_CLIENTMANAGER_H

class clientManager {
public:
    clientManager() = default;
    virtual ~clientManager() = 0;

    struct requestManager startClient(int);
    struct requestManager closeClient();
    struct requestManager statusClient(bool);
    struct requestManager addPlayer(int);
    struct requestManager deletePlayer();

private:
    int idClient;
    int isClient;
    int idPlayer;
    int isPlayer;
    struct requestManager {
        int firstParam;
        int secondParam;
    }
};

#endif //SKELETON_CLIENTMANAGER_H
