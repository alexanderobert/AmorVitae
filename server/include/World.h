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
#include <PacketManagerServer.h>
#include <NetServer.h>

const static int SECONDS_PER_MINUTE = 60;
const static int FRAMES_PER_SECOND = 25;

class World {
public:
    World(int player_count, int round_duration_minute, int port): netServer(port), player_count(player_count),
                                                                  round_duration(round_duration_minute){}
    void game_start();

private:

    ObjectManager objectManager;
    std::queue<std::shared_ptr<Event>> queque_event;
    NetServer netServer;
    int round_duration;
    int player_count;

    void calc_frame();
    std::shared_ptr<Player> init_user(User& user);
    void set_start_object();
    void serve_user(User& user);
    std::mutex events_m;
    bool need_update;
    int id_counter;
    std::mutex id_cointer_m;
};

void World::calc_frame() {
    while(true/*пока идет раунд*/) {
        std::map<int, std::shared_ptr<Object>>& objects = objectManager.get_objects_by_map();
        if (need_update) {
            for (auto& object: objects) {
                if (object.second->type != Object::STATIC_OBJECT) {
                    object.second->update();
                    auto collisions = objectManager.collisionSolver.check_object_collisions(objects, object.second);
                    for (auto& collision: collisions) {
                        if (collision->ID != object.second->ID) {
                            objectManager.collisionSolver.resolve_collision(object.second, collision);
                        }
                    }
                }
            }
            need_update = false;
        } else {
            std::lock_guard<std::mutex> lock(events_m);
            if (!queque_event.empty()) {
                std::shared_ptr<Event> event = queque_event.front();
                queque_event.pop();
                auto object = objectManager.get_object_by_id(event->IniciatorID);
                //Object new_state_object = event.get()->proccess(object); получаем новое стстояние обекиа
                auto New_state = event->proccess(object, objectManager);
                if (!objectManager.collisionSolver.is_object_collided(objects,
                                                                      New_state)) { //проверяем есть ли коллиизиb
                    //с новым состоянием
                    object = New_state;
                }
            }
            //обрабатываем ивент из очереди
        }
    }
};// При наличии флага обнавления вызывает update у всех обьектов, иначе исполняет Event

void World::game_start() {
    set_start_object();
    std::vector<User> players_init = netServer.accept_users(player_count);
    std::cout << "URAAAAAAAAAAAAAA))" << std::endl;
    std::vector<std::thread> threads;
    for (auto& usr: players_init) {
        objectManager.update_objects(init_user(usr));
        std::thread th([&](){
            this->serve_user(usr);
        });
        threads.push_back(move(th));
    }
    std::thread th([&](){
        this->calc_frame();
    });
    threads.push_back(move(th));
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
        std::cout<<"сдохни тварь"<<std::endl;
        std::shared_ptr<Event> event = netServer.get_client_action(user);
        std::lock_guard<std::mutex> lock(events_m);
        queque_event.push(event);

    }
}

std::shared_ptr<Player> World::init_user(User &user) {
    std::lock_guard<std::mutex>lg(id_cointer_m);
    Point position(id_counter * 10.0, id_counter* 10.0);
    std::shared_ptr<Player> player = std::make_shared<Player>(user.get_username(), position);
    return player;
}

void World::set_start_object() {
    std::lock_guard<std::mutex>lg(id_cointer_m);
    int layers = 6;
    double ring_r = 60;
    std::shared_ptr<Map> map = std::make_shared<Map>(id_counter, layers, ring_r);
    objectManager.update_objects(map);
    id_counter += player_count;
    Point pos(5,5);
    Point sight(1, 0);
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(id_counter, pos, sight);
    objectManager.update_objects(bullet);
    id_counter++;
    Point pos_p(5,5);
    std::shared_ptr<Player> player = std::make_shared<Player>(id_counter, pos);
    objectManager.update_objects(player);
    id_counter++;

}

#endif //AVM_WORLD_H