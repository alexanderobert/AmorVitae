//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_WORLD_H
#define AVM_WORLD_H

#include <vector>
#include "ObjectManager.h"
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

    std::vector<Object> calc_frame();
    std::vector<Object> calc_event(Event);
    Object init_user(User);
    void serve_user(User);

};

void World::game_start() {
    Users players_init = Netserver.Accept_users(player_count);
    for (const auto& usr: players_init) {
        ObjectManager.update_objects(init_user(usr));
       serve_user(usr); // в потоке
    }
}

void World::serve_user(User) {
    while(true) {
        Message = NetServer.Get_client_action(User);
        if (!Message.empty()) {
            Event event = EventManger.serve_Event(Message);
            ObjectManager.update_objects(calc_event(event));
            NetServer.Notify_all_users(calc_frame());
        }
    }

}

#endif //AVM_WORLD_H
