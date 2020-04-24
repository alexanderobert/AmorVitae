//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_WORLD_H
#define AVM_WORLD_H

#include <vector>
#include "ObjectManager.h"
#include "User.h"
#include "PacketManager.h"
#include "EventManager.h"
//#include "NetServer.h"

class World {
public:
    World(int player_count, int round_duration_sec, int port);
    void game_start();

private:

    ObjectManager objectManager;
    EventManager eventManager;
    NetServer netServer;
    int player_count;

    std::vector<Object> calc_frame();
    std::vector<Object> calc_event(Event*);
    Object init_user(User& user);
    void serve_user(User& user);

};

void World::game_start() {
    std::vector<User> players_init = Netserver.Accept_users(player_count);
    for (const auto& usr: players_init) {
        objectManager.update_objects(init_user(usr));
        serve_user(usr); // в потоке
    }
}

void World::serve_user(User& user) {
    while(true) {
        Message message = NetServer.Get_client_action(user);
        if (!Message.empty()) {
            Event* event = eventManager.serve_event(message);
            objectManager.update_objects(calc_event(event)); // перед изменение обьектов
                                                            // в методе update_objects мы захватываем мьютекс
            NetServer.Notify_all_users(calc_frame());
        }
    }

}

#endif //AVM_WORLD_H
