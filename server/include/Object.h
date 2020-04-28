//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H

#include <memory>

struct Point {
    double x, y;
    Point(double xpos, double ypos): x(xpos), y(ypos) {}
};

struct Vector {
    Point from, to;
    Vector(Point f, Point t):from(f), to(t){}
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
    void change_directoin(Vector new_dir);
    ~Player() override = default ;

    Point position;
    Vector sight;
    int speed;
    int pts;
};

class Obstruction : public  Object {
public:
    Obstruction(int id, Point pos, int h, int w): position(pos), width(w), height(h){
        ID = id;
    }
    Point position;
    int width, height;
};

class Bim: public Object {

public:
    Bim(int id, Point pos, Vector direct): position(pos), direction(direction){
        ID = id;
    }

    Point position;
    Vector direction;
    double width;
};

#endif //AVM_OBJECT_H
