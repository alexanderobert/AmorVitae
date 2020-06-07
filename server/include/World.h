//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_WORLD_H
#define AVM_WORLD_H

#include <vector>
#include <chrono>

#include <boost/thread/thread.hpp>

#include <queue>
#include <boost/date_time.hpp>
#include <ObjectManager.h>
#include <PacketManagerServer.h>
#include <NetServer.h>

const static int SECONDS_PER_MINUTE = 60;
const static double FRAMES_PER_SECOND = 15;

class World {
public:
    World(int player_count, int game_duration_minute, int port, int lay_count, double r_radius);
    void game_start();

private:

    void calc_frame();
    std::shared_ptr<Player> init_user(User& user);
    void set_start_object();
    void serve_user(User& user);

    ObjectManager objectManager;
    std::queue<std::shared_ptr<Event>> queque_event;
    NetServer netServer;
    Point map_centre;
    double tick_duration;
    double game_duration;
    int player_count;
    int layers_count;
    double ring_radius;

    std::mutex events_m;
    bool need_update;
    bool game_is_go_on;
};

#endif  // AVM_WORLD_H