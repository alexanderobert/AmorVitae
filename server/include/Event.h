//
// Created by moira-q on 14.04.20.
//

#ifndef AVM_EVENT_H
#define AVM_EVENT_H

#include <Object.h>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Event {
public:
    Event(int Player_ID, Vector sight_direct):IniciatorID(Player_ID), sight(sight_direct) {};
    virtual std::shared_ptr<Object> proccess(std::shared_ptr<Object>) {};
    virtual ~Event() = default;
    int IniciatorID;
    Vector sight;
};

class Move: public Event {
public:
    Move(int Player_ID, Vector sight_direct, Direction dir): Event(Player_ID, sight_direct), direction(dir) {}
    ~Move() override = default ;
    std::shared_ptr<Object> proccess(std::shared_ptr<Object> obj) override {
        Player player = *std::dynamic_pointer_cast<Player>(obj).get();

        switch (direction) {
            case UP: {
                player.position.y += player.speed;
                break;
            }
            case DOWN:{
                player.position.y -= player.speed;
                break;
            }
            case LEFT:{
                player.position.x -= player.speed;
                break;
            }
            case RIGHT:{
                player.position.y += player.speed;
                break;
            }
            default:
                break;
        }
        return std::make_shared<Player>(player);
        //obj.get()->position.;
    }
    Direction direction;

};

class Blink: public Event {
    const static int BLINK_RANGE = 1000;
public:
    Blink(int Player_ID, Vector sight_direct): Event(Player_ID, sight_direct) {};
    ~Blink() override = default ;
    std::shared_ptr<Object> proccess(std::shared_ptr<Object> obj) override {
        Player player = *std::dynamic_pointer_cast<Player>(obj).get();
        player.sight = player.normalize(sight);
        player.position = player.position + player.sight * BLINK_RANGE;
        return std::make_shared<Player>(player);
    }
};

#endif //AVM_EVENT_H