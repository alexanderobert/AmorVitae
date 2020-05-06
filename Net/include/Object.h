//
// Взял object у сервера
//

#ifndef AMORVITAE_OBJECT_H
#define AMORVITAE_OBJECT_H

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
    enum Type {
        STATIC_OBJECT,
        PLAYER_OBJECT,
        BULLET_OBJECT
    };
    Object(Type t, int id, Point pos, Model mod):type(t), ID(id), position(pos), model(mod) {}
    virtual void update() {}
    virtual ~Object() = 0;
    Point position;
    Model model;
    Type type;
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
    Player(int id, Point pos): Object(Type::PLAYER_OBJECT, id, pos, Model(30,30)),
                               sight({0,0}, {0,0}), speed(50) {};
    void update() override;//обновление в зависимости от state
    ~Player() override = default ;
    Vector sight;
    PlayerState state_;
    int speed;
};

class Map : public  Object {
public:
    Map();
    void update() override; //Добавляет очки, меняет зону
    void next_stage();
    int layers_count;
    double ring_radius;
    std::map<int, int> players_pts;
    std::map<int, int> pts_table;

};

class Obstruction : public  Object {
public:
    Obstruction(int id, Point pos, int h, int w): Object(Type::STATIC_OBJECT, id, pos, Model(30,30)) {};
};
/*
class Bim: public Object {
public:
    Bim(int id, Point pos, Vector direct): position(pos), direction(direction){
        ID = id;
    }
    Point position;
    Vector direction;
    double width;
};*/


#endif //AMORVITAE_OBJECT_H
