//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H

#include <memory>
#include <map>
#include <cmath>

struct Point {
    double x, y;
    Point(double xpos, double ypos): x(xpos), y(ypos) {}
    Point operator+ (const Point& rhs) {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    Point operator- (const Point& rhs) {
        return {this->x - rhs.x, this->y - rhs.y};
    }
    Point operator* (int value) {
        return {this->x * value, this->y * value};
    }
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
        BULLET_OBJECT,
        MAP_OBJECT
    };
    Object(Type t, int id, Point pos, Model mod):type(t), ID(id), position(pos), model(mod) {}
    virtual void update() {}
    virtual ~Object() = default;
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
                               sight(1, 0), speed(50) {};
    void update() override {
        if (state_.get_state() == PlayerState::STATE_FLYING) {
            position = position +  sight * speed;
        }
    }//обновление в зависимости от state
    ~Player() override = default ;
    PlayerState state_;
    Point sight;
    int speed;
    Point normalize(const Vector& vec) {
        double t1 = vec.to.x - vec.from.x;
        double t2 = vec.to.y - vec.from.y;
        double l = sqrt(t1 * t1 + t2 * t2);
        return {t1 / l, t2 / l};
    }
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

class BulletState {
        public:
        enum State {
            ACTIVE,
                    INACTIVE
        };
        BulletState(): state_(State::ACTIVE), live_tick(0) {};
        void state_to_inactive() {
            if (state_ == State::ACTIVE) {
                state_ = State::INACTIVE;
            }
        }
        State get_state() {
            next_tick();
            return state_;
        }
        private:
        void next_tick() {
            live_tick++;
            if (live_tick > 60) {
                state_ = State::INACTIVE;
                live_tick = 0;
            }
        };
        int live_tick;
        State state_;
};

class Bullet : public  Object {
public:
    Bullet(int id, Point pos, Point sight): Object(Type::BULLET_OBJECT, id, pos, Model(15,15)),
                                            sight(sight), speed(300) {};

    void update() override {
        if (state.get_state() == BulletState::ACTIVE) {
            position = position +  sight * speed;
        }
    }
    BulletState state;
    Point sight;
    int speed;
};
#endif //AVM_OBJECT_H
