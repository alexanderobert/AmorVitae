#ifndef SKELETON_PLAYER_H
#define SKELETON_PLAYER_H

class player {
public:
    player() = default;
    virtual ~player() = 0;

    struct requestManager shareParams();
private:
    int idPlayer;
    int height;
    int width;
};

#endif //SKELETON_PLAYER_H
