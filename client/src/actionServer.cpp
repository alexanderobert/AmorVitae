#include "actionServer.h"

void actionServer::getActionKey(std::string key){
    json actionMessage;

    actionMessage["eventType"] = "action";
    actionMessage["action"] = {{"move", key}};


    //std::cout<<actionMessage; //проверка

    // send_action(actionMessage); from NetClient
}

void actionServer::getActionMousePos(int x, int y){
    json actionMessage;

    actionMessage["eventType"] = "action";
    actionMessage["mouse_coordinate"] = {{"x", x}, {"y", y}};

    //std::cout<<actionMessage;

    // send_action(actionMessage); from NetClient
}

void actionServer::sendActionMove(Direction direction){

    Move event;
    event.type = move;
    event.direction = direction;
    event.sight = mySight;


    //std::cout<<event.sight.to.x<<"\n";
    //std::cout<<event.sight.to.y<<"\n";

    // Send_action(event); from NetClient
}

void actionServer::sendActionBlink(){

    Blink event;
    event.type = blink;
    event.sight = mySight;

    //std::cout<<"Блинк"<<"\n";

    // Send_action(event); from NetClient
}

void actionServer::updatePosition(){

    myPosition.x = 500;
    myPosition.y = 500;
}

void actionServer::updateSight(int x, int y){

    Point mouse;
    mouse.x = x;
    mouse.y = y;

    myPosition.x = 500;
    myPosition.y = 500;

    mySight.from = myPosition;
    mySight.to = mouse;
}


Object actionServer::getMessage(){

    // return Get_servet_action(); from NetClient

    Object object;
    object.type = STATIC_OBJECT;

    return object;
}