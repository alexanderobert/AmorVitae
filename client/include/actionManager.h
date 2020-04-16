#ifndef SKELETON_ACTIONMANAGER_H
#define SKELETON_ACTIONMANAGER_H

class actionManager {
public:
    actionManager() = default;
    virtual ~actionManager() = 0;

    struct action pollAction();
private:
    struct action;
};

#endif //SKELETON_ACTIONMANAGER_H
