//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_WORLD_H
#define AVM_WORLD_H

#include <vector>
#include <thread>
#include <chrono>
#include "ObjectManager.h"
#include "User.h"
#include "PacketManager.h"
#include "EventManager.h"

//#include "NetServer.h"
const int SECONDS_PER_MINUTE = 60;
const int FRAMES_PER_SECOND = 25;

class World {
public:
    World(int player_count, int round_duration_minute, int port);
    void game_start();

private:

    ObjectManager objectManager;
    EventManager eventManager;
    NetServer netServer;
    int round_duration;
    int player_count;

    void calc_frame();
    std::vector<Object> calc_event(Event*);
    Object init_user(User& user);
    void serve_user(User& user);

};

void World::game_start() {
    std::vector<User> players_init = Netserver.Accept_users(player_count);
    for (const auto& usr: players_init) {
        objectManager.update_objects(init_user(usr));
        std::thread th([&](){
            this->serve_user(usr);
        });
        th.detach();
    }
    auto round_start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;
    while (duration.count() < round_duration) {
        if (/*прошло нужное колво тиков*/ true) {
            calc_frame();
        }
        NetServer.Notify_all_users(objectManager.get_objects_by_array());
        auto curr_time = std::chrono::high_resolution_clock::now();
        duration = curr_time - round_start;
    }
}

void World::serve_user(User& user) {
    while(true) {
        Message message = NetServer.Get_client_action(user);
        if (!Message.empty()) {
            Event* event = eventManager.serve_event(message);
            objectManager.update_objects(calc_event(event)); // перед изменение обьектов
                                                            // в методе update_objects мы захватываем мьютекс
        }
    }
}

#endif //AVM_WORLD_H
