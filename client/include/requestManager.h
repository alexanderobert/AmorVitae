#ifndef SKELETON_REQUESTMANAGER_H
#define SKELETON_REQUESTMANAGER_H

#include <queue>

class requestManager {
public:
    requestManager() = default;
    virtual ~requestManager() = 0;

    void addQueue(struct RequestManager);
    void deleteQueue(struct RequestManager);
    void createInitRequest(struct RequestManager);
    void createEditRequest(struct RequestManager);
    struct RequestManager checkTypeRequest(struct RequestManager);
private:
    std::queue <struct requestManager> requests;
    bool objectState;
    struct RequestManager{
        int firstParam;
        int secondParam;
    };

};

#endif //SKELETON_REQUESTMANAGER_H
