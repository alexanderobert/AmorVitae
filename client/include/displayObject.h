#ifndef SKELETON_DISPLAYOBJECT_H
#define SKELETON_DISPLAYOBJECT_H


class displayObject {
public:
    displayObject() = default;
    virtual ~displayObject() = 0;

    void createDraw(struct objectGrid);
    void editDraw(struct objectGrid);
    void deleteDraw(struct objectGrid);
private:
    struct objectGrid{
        int firstParam;
        int secondParam;
        int thirdParam;
    };
};

#endif //SKELETON_DISPLAYOBJECT_H
