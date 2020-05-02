//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_WORLD_H
#define AVM_WORLD_H

#include <vector>
#include <thread>
#include <chrono>
#include <queue>
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
    std::vector<std::unique_ptr<Event>> queque_event;
    NetServer netServer;
    int round_duration;
    int player_count;

    void calc_frame();
    void calc_event(Event& event);
    Object init_user(User& user);
    void serve_user(User& user);
    std::mutex events;
    bool need_update;
};

void World::calc_frame()    {};// При наличии флага обнавления вызывает update у всех обьектов, иначе исполняет Event

void World::game_start() {
    std::vector<User> players_init = netServer.Accept_users(player_count);
    std::vector<std::thread> threads;
    for (auto& usr: players_init) {
        objectManager.update_objects(init_user(usr));
        std::thread th([&](){
            this->serve_user(usr);
        });
        threads.push_back(th);
    }
    std::thread th([&](){
        this->calc_frame();
    });
    threads.push_back(th);
    auto round_start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;
    while (duration.count() < round_duration) {
        if (/*прошло нужное колво тиков*/ true) {
            need_update = true;
            netServer.Notify_all_users(objectManager.get_objects_by_map());
        }
        auto curr_time = std::chrono::high_resolution_clock::now();
        duration = curr_time - round_start;
    }
    for (auto& th: threads) {
        th.join();
    }
}

void World::serve_user(User& user) {
    while(user.is_connected()) {
        Message message = netServer.Get_client_action(user);
        if (!Message.empty()) {
            std::unique_ptr<Event> event = eventManager.serve_event(message);
            queque_event.push_back(event);
        }
    }
}

#endif //AVM_WORLD_H