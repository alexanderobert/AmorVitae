//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H

struct Point {
    int x, y;
    Point(int xpos, int ypos): x(xpos), y(ypos) {}
};

struct Direction {
    Point from, to;
    Direction(Point f, Point t):from(f), to(t){}
};



class Object {
public:
    Object() = default;
    virtual ~Object() = 0;
    int ID;
};

class Player : public Object {
public:
    Player(int id, Point pos): position(pos), pts(0), sight({0,0}, {0,0}) {
        ID = id;
    };
    void change_position(Point new_pos);
    void change_directoin(Direction new_dir);
    ~Player() override = default ;

    Point position;
    Direction sight;
    int pts;
};

class Obstruction : public  Object {
    Obstruction(int id, Point pos, int h, int w): position(pos), width(w), height(h){
        ID = id;
    }
    Point position;
    int width, height;
};

#endif //AVM_OBJECT_H
