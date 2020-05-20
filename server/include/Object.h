//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H

#include <memory>
#include <map>
#include <vector>
#include <cmath>

const static double DEFAULT_BULLET_SPEED = 10;
const static double DEFAULT_PLAYER_SPEED = 1;

struct Point {
    double x, y;
    Point(double xpos, double ypos): x(xpos), y(ypos) {}
    Point operator+ (const Point& rhs) {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    Point operator- (const Point& rhs) {
        return {this->x - rhs.x, this->y - rhs.y};
    }
    Point operator* (double value) {
        return {this->x * value, this->y * value};
    }
    double distance_between(const Point& other) {
        return sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
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
    virtual void update()  = 0;
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
        if (flying_tick > 10) {
            state_ = State::STATE_STANDING;
            flying_tick = 0;

        }
    };
    int flying_tick;
    State state_;
};

class Player : public Object {
public:
    Player(int id, Point pos): Object(Type::PLAYER_OBJECT, id, pos, Model(15,15)),
                               sight(1, 0), speed(DEFAULT_PLAYER_SPEED) {};
    void update() override {
        if (state_.get_state() == PlayerState::STATE_FLYING) {
            position = position +  sight * speed;
        }
    }//обновление в зависимости от state
    PlayerState state_;
    Point sight;
    double speed;
    Point normalize(const Vector& vec) {
        double t1 = vec.to.x - vec.from.x;
        double t2 = vec.to.y - vec.from.y;
        double l = sqrt(t1 * t1 + t2 * t2);
        return {t1 / l, t2 / l};
    }
};

class Map : public  Object {
public:
    Map(int id, int layers, double ring_r, int durations_tick, std::vector<std::shared_ptr<Object>> plrs):
            Object(Type::MAP_OBJECT, id, Point(0, 0), Model(0, 0)), layers_count(layers), ring_radius(ring_r),
            game_duration_ticks(durations_tick), current_round_tick(0), players(move(plrs)),
            map_centr({layers_count * ring_radius, layers_count * ring_radius}) {
        for (int i = 1; i <= layers_count; ++i) {
            pts_table[i] = i * 2;
        }
    }
    void update() override {
        current_round_tick++;
        for (const auto& player: players) {
            add_points_to_player(player);
        }
        if(layers_count != 0 ) {
            if ((game_duration_ticks / layers_count) < current_round_tick) {
                current_round_tick = 0;
                next_stage();
            }
        }

    } //Добавляет очки, меняет зону
    std::map<int, int> players_pts;
    std::map<int, int> pts_table;
    int layers_count;
    double ring_radius;
private:
    void next_stage() {
        layers_count--;
    }
    void add_points_to_player(const std::shared_ptr<Object>& player) {
        int position_rating = layers_count - (map_centr.distance_between(player->position) / layers_count);
        players_pts[player->ID] += pts_table[position_rating];
    }
    int current_round_tick;
    int game_duration_ticks;
    std::vector<std::shared_ptr<Object>> players;

    Point map_centr;
};

class Obstruction : public  Object {
public:
    Obstruction(int id, Point pos, int h, int w): Object(Type::STATIC_OBJECT, id, pos, Model(h,w)) {};
};

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
    Bullet(int id, Point pos, Point sight, int iniciator_id): Object(Type::BULLET_OBJECT, id, pos, Model(7,7)),
                                                              sight(sight), speed(DEFAULT_BULLET_SPEED), iniciator_ID(iniciator_id) {};

    void update() override {
        if (state.get_state() == BulletState::ACTIVE) {
            position = position +  sight * speed;
        }
    }
    BulletState state;
    Point sight;
    int iniciator_ID;
    double speed;
};
#endif //AVM_OBJECT_H