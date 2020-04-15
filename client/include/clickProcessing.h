#ifndef SKELETON_CLICKPROCESSING_H
#define SKELETON_CLICKPROCESSING_H


class clickProcessing {
public:
    clickProcessing() = default;
    virtual ~clickProcessing() = 0;
    int pollEvent(int event);
    int closeEvent(int event);
    int resizedEvent(int event);
    int lostFocusEvent(int event);
    int gainedFocusEvent(int event);
    int textEnteredEvent(int event);
    int keyPressedEvent(int event);
    int keyReleasedEvent(int event);
    int mouseWheelScrolledEvent(int event);
    int mouseButtonPressedEvent(int event);
    int mouseButtonReleasedEvent(int event);
    struct point mouseMovedEvent(int event);
private:
    int typeOfEvent;
    struct point{
        int firstParam;
        int secondParam;
    };
};


#endif //SKELETON_CLICKPROCESSING_H
