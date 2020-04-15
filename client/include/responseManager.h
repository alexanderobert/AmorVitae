#ifndef SKELETON_RESPONSEMANAGER_H
#define SKELETON_RESPONSEMANAGER_H

class responseManager {
public:
    responseManager() = default;
    virtual ~responseManager() = 0;

    struct drawObject parseEdit(struct message);
    void graphicRequets(struct drawObject);
private:

    struct message{
        int firstParam;
        int secondParam;
    };
};

#endif //SKELETON_RESPONSEMANAGER_H
