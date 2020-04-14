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

};

void World::game_start() {
     players_init = EventManager.Serve_Event(Netserver.Accept_users(player_count);
    for(const auto& event: players_init) {
        ObjectManager.update_objects(calc_event(event));
    }

    while(true) {
        Message = NetServer.Get_clients_actions();
        if(!Message.empty()) {
            Event event = EventManger.serve_Event(Message);
            ObjectManager.update_objects(calc_event(event));
        }

        NetServer.Notify_all_users(calc_frame());
    }
}


#endif //AVM_WORLD_H
