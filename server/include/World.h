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
const static double FRAMES_PER_SECOND = 25;

class World {
public:
    World(int player_count, int game_duration_minute, int port, int lay_count, double r_radius):
          netServer(port), player_count(player_count), layers_count(lay_count), ring_radius(r_radius){
        game_duration = game_duration_minute * SECONDS_PER_MINUTE;
        tick_duration = 1 / FRAMES_PER_SECOND;
    }
    void game_start();

private:

    ObjectManager objectManager;
    std::queue<std::shared_ptr<Event>> queque_event;
    NetServer netServer;
    double tick_duration;
    double game_duration;
    int player_count;
    int layers_count;
    double ring_radius;

    void calc_frame();
    std::shared_ptr<Player> init_user(User& user);
    void set_start_object();
    void serve_user(User& user);
    std::mutex events_m;
    bool need_update;
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
                        objectManager.collisionSolver.resolve_collision(object.second, collision);
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
                if (!objectManager.collisionSolver.is_object_collided(objects, New_state)) { //проверяем есть ли коллиизиb
                    //с новым состоянием
                    *object = *New_state;
                    // objectManager.update_objects(New_state);
                    std::cout << "Ура  новое положение игрока: " << object->position.x << ' ' << object->position.y << std::endl;

                }
            }
            //обрабатываем ивент из очереди
        }
    }
};// При наличии флага обнавления вызывает update у всех обьектов, иначе исполняет Event

void World::game_start() {
    std::vector<User> players_init = netServer.accept_users(player_count, objectManager);
    std::vector<std::thread> threads;
    for (auto& usr: players_init) {
        objectManager.update_objects(init_user(usr));
        std::thread th([&](){
            this->serve_user(usr);
        });
        threads.push_back(move(th));
    }
    set_start_object();
    std::thread th([&](){
        this->calc_frame();
    });
    threads.push_back(move(th));
    auto round_start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> current_game_duration(0);
    std::chrono::duration<double> current_tick_duration(0);
    auto last_tick = std::chrono::high_resolution_clock::now();
    while (current_game_duration.count() < game_duration) {
        auto curr_time = std::chrono::high_resolution_clock::now();
        current_tick_duration = curr_time - last_tick;
        if (current_tick_duration.count() > tick_duration) {
            last_tick = curr_time;
            need_update = true;
            netServer.notify_all_users(objectManager.get_objects_by_map());
        }
        curr_time = std::chrono::high_resolution_clock::now();
        current_game_duration = curr_time - round_start;
    }
    for (auto& th: threads) {
        th.join();
    }
}

void World::serve_user(User& user) {
    while(user.is_connected()) {
        std::shared_ptr<Event> event = netServer.get_client_action(user);
        std::lock_guard<std::mutex> lock(events_m);
        queque_event.push(event);
    }
}

std::shared_ptr<Player> World::init_user(User &user) {
    Point position(ring_radius * layers_count, ring_radius * layers_count);
    std::shared_ptr<Player> player = std::make_shared<Player>(user.get_username(), position);
    return player;
}

void World::set_start_object() {
    std::vector<std::shared_ptr<Object>> players;
    for (int i = 0; i < player_count; i++) {
        players.push_back(objectManager.get_object_by_id(i));
    }
    std::shared_ptr<Map> map = std::make_shared<Map>(objectManager.pick_enable_id(), layers_count, ring_radius,
                                                     game_duration * FRAMES_PER_SECOND, move(players));
    objectManager.update_objects(map);

    std::shared_ptr<Bullet> bll = std::make_shared<Bullet>(objectManager.pick_enable_id(), Point(100, 500), Point(1,0), 20);
    objectManager.update_objects(bll);

    std::shared_ptr<Obstruction> obs = std::make_shared<Obstruction>(objectManager.pick_enable_id(), Point(100, 100), 100, 100);
    objectManager.update_objects(obs);



}

#endif //AVM_WORLD_H