#ifndef SKELETON_EVENT_H
#define SKELETON_EVENT_H

class event {
    public:
    event() = default;
        virtual ~event() = 0;

    int type;
    //eventParametrs;
    int eventIniciaritID;
    void process(Object);
};

#endif //SKELETON_EVENT_H
