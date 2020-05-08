//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_WORLD_H
#define AVM_WORLD_H

#include <vector>
#include <thread>
#include <chrono>
#include <queue>
#include <ObjectManager.h>
#include <PacketManager.h>
#include <EventManager.h>
#include <NetServer.h>

const static int SECONDS_PER_MINUTE = 60;
const static int FRAMES_PER_SECOND = 25;

class World {
public:
    World(int player_count, int round_duration_minute, int port);
    void game_start();

private:

    ObjectManager objectManager;
    EventManager eventManager;
    std::queue<std::shared_ptr<Event>> queque_event;
    NetServer netServer;
    int round_duration;
    int player_count;

    void calc_frame();
    std::shared_ptr<Object> init_user(User& user);
    void serve_user(User& user);
    std::mutex events_m;
    bool need_update;
    int current_id;
};

void World::calc_frame() {
    while(true/*пока идет раунд*/) {
        std::map<int, std::shared_ptr<Object>>& objects = objectManager.get_objects_by_map();
        if (need_update) {
            for (auto& object: objects) {
                if (object.second->type != Object::STATIC_OBJECT) {
                    object.second->update();
                    std::vector<std::shared_ptr<Object>&> collisions =
                            objectManager.collisionSolver.check_object_collisions(objects, object.second);
                    for (auto& collision: collisions) {
                        objectManager.collisionSolver.resolve_collision(object, collision);
                    }
                }
            }
            need_update = false;
        } else {
            std::lock_guard<std::mutex> lock(events_m);
            std::shared_ptr<Event> event = queque_event.front();
            queque_event.pop();
            auto object = objectManager.get_object_by_id(event->IniciatorID);
            //Object new_state_object = event.get()->proccess(object); получаем новое стстояние обекиа
            auto New_state =event->proccess(object);
            if(!objectManager.collisionSolver.is_object_collided(objects, New_state)) { //проверяем есть ли коллиизиb
                                                                                    //с новым состоянием
                object = New_state;
            }
            //обрабатываем ивент из очереди
        }
    }
};// При наличии флага обнавления вызывает update у всех обьектов, иначе исполняет Event

void World::game_start() {
    std::vector<User> players_init = netServer.accept_users(player_count);
    std::vector<std::thread> threads;
    for (auto& usr: players_init) {
        objectManager.update_objects(std::make_shared<Player>(init_user(usr)));
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
        if (/*прошло нужное колво времени*/ true) {
            need_update = true;
            netServer.notify_all_users(objectManager.get_objects_by_map());
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
        Message message = netServer.get_client_action(user);
        if (!message.empty()) {
            std::shared_ptr<Event> event = eventManager.serve_event(message);
            std::lock_guard<std::mutex> lock(events_m);
            queque_event.push(event);
        }
    }
}

#endif //AVM_WORLD_H