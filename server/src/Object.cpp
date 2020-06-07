//
// Created by moira-q on 14.04.20.
//

#include <Object.h>

#include <include/Object.h>


Point Point::operator+(const Point &rhs) const {
    return {this->x + rhs.x, this->y + rhs.y};
}

Point Point::operator-(const Point &rhs) const {
    return {this->x - rhs.x, this->y - rhs.y};
}

Point Point::operator*(double value) const {
    return {this->x * value, this->y * value};
}

double Point::distance_between(const Point &other) const {
    return sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
}

PlayerState::State PlayerState::get_state() {
    next_flying_tick();
    next_shot_tick();
    next_blink_tick();
    return state_;
}

bool PlayerState::is_shot_avaible() const {
    return !is_shot_cd;
}

bool PlayerState::is_blink_avaible() const {
    return !is_blink_cd;
}

void PlayerState::blink() {
    is_blink_cd = true;
}

void PlayerState::shot() {
    is_shot_cd = true;
}

void PlayerState::state_to_fly() {
    if (state_ != State::STATE_FLYING) {
        state_ = State::STATE_FLYING;
    }
}

void PlayerState::next_flying_tick() {
    if (state_ == State::STATE_FLYING) {
        flying_tick++;
        if (flying_tick > FLYING_DURATION) {
            state_ = State::STATE_STANDING;
            flying_tick = 0;
        }
    }
}

void PlayerState::next_shot_tick() {
    if (is_shot_cd) {
        shot_cd_tick++;
        if (shot_cd_tick > SHOT_COULDOWN_TICKS) {
            is_shot_cd = false;
            shot_cd_tick = 0;
        }
    }
}

void PlayerState::next_blink_tick() {
    if (is_blink_cd) {
        blink_cd_tick++;
        if (blink_cd_tick > BLINK_COULDOWN_TICKS) {
            is_blink_cd = false;
            blink_cd_tick = 0;
        }
    }
}

void Player::update() {
    if (state_.get_state() == PlayerState::STATE_FLYING) {
        position = position +  sight * speed;
    } else {
        speed = DEFAULT_PLAYER_SPEED;
    }
}

Point Player::normalize(const Vector &vec) const {
    double t1 = vec.to.x - vec.from.x;
    double t2 = vec.to.y - vec.from.y;
    double l = sqrt(t1 * t1 + t2 * t2);
    return {t1 / l, t2 / l};
}

Map::Map(int id, int layers, double ring_r, int durations_tick, std::vector<std::shared_ptr<Object>> plrs):
         Object(Type::MAP_OBJECT, id, Point(0, 0), Model(0, 0)), layers_count(layers), ring_radius(ring_r),
         game_duration_ticks(durations_tick), current_round_tick(0), players(move(plrs)),
         map_centr({WINDOW_W/ 2}, {WINDOW_H / 2}) {

    for (int i = 1; i <= layers_count; ++i) {
        pts_table[i] = i;
    }
    for(const auto& player: players) {
        players_pts[player->ID] = 0;
    }
}

void Map::update() {
    current_round_tick++;
    for (const auto& player: players) {
        add_points_to_player(player);
    }
    if(layers_count != 0 ) {
        if ((game_duration_ticks / (layers_count + 1)) < current_round_tick) {
            current_round_tick = 0;
            next_stage();
        }
    }
}

void Map::next_stage() {
    layers_count--;
}

void Map::add_points_to_player(const std::shared_ptr<Object> &player) {
    int position_rating = (map_centr.distance_between(player->position) / ring_radius);
    if (position_rating < layers_count) {
        players_pts[player->ID] += pts_table[pts_table.size() - position_rating];
    }
}

void BulletState::state_to_inactive() {
    if (state_ == State::ACTIVE) {
        state_ = State::INACTIVE;
    }
}

BulletState::State BulletState::get_state() {
    next_tick();
    return state_;
}

void BulletState::next_tick() {
    live_tick++;
    if (live_tick > BULLET_TICKS_LIVETIME) {
        state_ = State::INACTIVE;
        live_tick = 0;
    }
}

void Bullet::update() {
    if (state.get_state() == BulletState::ACTIVE) {
        position = position +  sight * speed;
    }
}
