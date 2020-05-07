#include "../include/actionServer.h"

void actionServerInterface::sendActionMove(Direction direction){

    Move event;
    event.type = move;
    event.direction = direction;
    event.sight = mySight;


    //std::cout<<event.sight.to.x<<"\n";
    //std::cout<<event.sight.to.y<<"\n";

    // Send_action(event); from NetClient
}

void actionServerInterface::sendActionBlink(){

    Blink event;
    event.type = blink;
    event.sight = mySight;

    //std::cout<<"Блинк"<<"\n";

    // Send_action(event); from NetClient
}

void actionServerInterface::updatePosition(){

    myPosition.x = 500;
    myPosition.y = 500;
}

void actionServerInterface::updateSight(int x, int y){

    Point mouse;
    mouse.x = x;
    mouse.y = y;

    myPosition.x = 500;
    myPosition.y = 500;

    mySight.from = myPosition;
    mySight.to = mouse;
}


ObjectInterface actionServerInterface::getMessage(){

    // return Get_servet_action(); from NetClient

    ObjectInterface object;
    object.type = STATIC_OBJECT;

    return object;
}