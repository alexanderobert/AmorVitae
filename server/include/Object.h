//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H

#include <memory>
#include <map>

struct Point {
    double x, y;
    Point(double xpos, double ypos): x(xpos), y(ypos) {}
};

struct Vector {
    Point from, to;
    Vector(Point f, Point t):from(f), to(t){}
};

struct Model {
    int height, width;
    Model(int h, int w):height(h), width(w) {}
};

class Object {
public:
    Object() = default;
    virtual void update() {}
    virtual ~Object() = 0;
    int ID;
};

class PlayerState {
public:
    enum State {
        STATE_STANDING,
        STATE_FLYING
    };
    PlayerState(): state_(State::STATE_STANDING), flying_tick(0) {};
    State get_state() {
        if (state_ == State::STATE_FLYING) {
            next_flying_tick();
        }
        return state_;
    }
    void state_to_fly() {
        if (state_ != State::STATE_FLYING) {
            state_ = State::STATE_FLYING;
        }
    }

private:
    void next_flying_tick() {
        flying_tick++;
        if (flying_tick > 60) {
            state_ = State::STATE_STANDING;
            flying_tick = 0;
        }
    };
    int flying_tick;
    State state_;
};

class Player : public Object {
public:
    Player(int id, Point pos): position(pos), sight({0,0}, {0,0}), model(30, 30) {
        ID = id;
    };
    void update() override;//обновление в зависимости от state
    ~Player() override = default ;
    Point position;
    Vector sight;
    PlayerState state_;
    Model model;
    int speed;
};

class Map : public  Object {
public:
    Map();
    void update() override; //Добавляет очки, меняет зону
    void next_stage();
    int layers_count;
    Point position;
    double ring_radius;
    std::map<int, int> players_pts;
    std::map<int, int> pts_table;

};

class Obstruction : public  Object {
public:
    Obstruction(int id, Point pos, int h, int w): position(pos), model(h, w){
        ID = id;
    }
    Point position;
    Model model;
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
