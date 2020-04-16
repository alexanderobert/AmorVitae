#ifndef SKELETON_ACTIONSERVER_H
#define SKELETON_ACTIONSERVER_H

class actionServer {
public:
    actionServer() = default;
    virtual ~actionServer() = 0;

    struct event getEvent();
    struct action getAction();
    struct message makeMessage(action, event);
private:
    int eventType;
    //eventParametrs;
    struct event;
    struct action;
    struct message;
};

#endif //SKELETON_ACTIONSERVER_H
