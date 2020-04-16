#ifndef SKELETON_DISPLAYMANAGER_H
#define SKELETON_DISPLAYMANAGER_H

class displayManager {
public:
    displayManager () = default;
    virtual ~displayManager () = 0;

    struct playerData createPlayerData(struct message);
    struct projectileData createProjectileData(struct message);
    struct mapCode createMapCode(struct message);
    struct Config createConfig(struct message);
private:
    struct message;
};

#endif //SKELETON_DISPLAYMANAGER_H
