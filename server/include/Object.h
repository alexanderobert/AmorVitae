//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_OBJECT_H
#define AVM_OBJECT_H

#include <memory>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>

const static double DEFAULT_BULLET_SPEED = 20;
const static double DEFAULT_PLAYER_SPEED = 3;
const static int SHOT_COULDOWN_TICKS = 15;
const static int BLINK_COULDOWN_TICKS = 120;
const static int BULLET_TICKS_LIVETIME = 250;
const static int FLYING_DURATION = 15;

const static int WINDOW_H = 800;
const static int WINDOW_W = 1280;


struct Point {
    double x, y;
    Point() = default;
    Point(double xpos, double ypos): x(xpos), y(ypos) {}
    Point operator+ (const Point& rhs) const;
    Point operator- (const Point& rhs) const;
    Point operator* (double value) const;
    double distance_between(const Point& other) const;

};

struct Vector {
    Point from, to;
    Vector(Point f, Point t):from(f), to(t){}
};

struct Model {
    int height, width;
    Model(int w, int h):height(h), width(w) {}
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
    PlayerState(): state_(State::STATE_STANDING), flying_tick(0), shot_cd_tick(0) {};
    State get_state();
    bool is_shot_avaible() const;
    bool is_blink_avaible() const;
    void blink();
    void shot();
    void state_to_fly();

private:
    void next_flying_tick();
    void next_shot_tick();
    void next_blink_tick();

    int flying_tick;
    int shot_cd_tick;
    int blink_cd_tick;
    bool is_blink_cd;
    bool is_shot_cd;
    State state_;
};

class Player : public Object {
public:
    Player(int id, Point pos): Object(Type::PLAYER_OBJECT, id, pos, Model(26,26)),
                               sight(1, 0), speed(DEFAULT_PLAYER_SPEED) {};
    void update() override;  // обновление в зависимости от state
    PlayerState state_;
    Point sight;
    double speed;
    Point normalize(const Vector& vec) const;
};

class Map : public  Object {
public:
    Map(int id, int layers, double ring_r, int durations_tick, std::vector<std::shared_ptr<Object>> plrs);
    void update() override;  // Добавляет очки, меняет зону

    std::map<int, int> players_pts;
    std::map<int, int> pts_table;
    int layers_count;
    double ring_radius;

private:
    void next_stage();
    void add_points_to_player(const std::shared_ptr<Object>& player);

    int current_round_tick;
    int game_duration_ticks;
    std::vector<std::shared_ptr<Object>> players;
    Point map_centr;
};

class Obstruction : public  Object {
public:
    Obstruction(int id, Point pos, int w, int h): Object(Type::STATIC_OBJECT, id, pos, Model(w,h)) {};
    void update() override {}
};

class BulletState {
public:
    enum State {
        ACTIVE,
        INACTIVE
    };
    BulletState(): state_(State::ACTIVE), live_tick(0) {};
    void state_to_inactive();
    State get_state();

private:
    void next_tick();

    int live_tick;
    State state_;
};

class Bullet : public  Object {
public:
    Bullet(int id, Point pos, Point sight, int iniciator_id): Object(Type::BULLET_OBJECT, id, pos, Model(7,7)),
                                                              sight(sight), speed(DEFAULT_BULLET_SPEED),
                                                              iniciator_ID(iniciator_id) {};

    void update() override;

    BulletState state;
    Point sight;
    int iniciator_ID;
    double speed;
};
#endif //AVM_OBJECT_H