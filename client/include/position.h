#ifndef SKELETON_POSITION_H
#define SKELETON_POSITION_H

class position {
public:
    position() = default;
    virtual ~position() = 0;

    void getPosition(int idPlayer);
    struct Position sharePosition(struct Position);
private:
    struct Position{
        int firstParam;
        int secondParam;
    };
};

#endif //SKELETON_POSITION_H
