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

    MessageToServer message;
    message.type = move;
    message.direction = direction;

    //std::cout<<message.direction<<"\n";

    // Send_action(message); from NetClient
}

void actionServer::sendActionBlink(){

    MessageToServer message;
    message.type = blink;

    // Send_action(message); from NetClient
}

void actionServer::sendActionChangeSight(int x, int y){

    MousePosition mouse;
    mouse.x = x;
    mouse.y = y;

    MessageToServer  message;
    message.type = changeSight;
    message.newSight = mouse;

    //std::cout<<message.newSight.x<<" "<<message.newSight.y<<"\n";

    // Send_action(message); from NetClient
}


MessageFromServer actionServer::getMessage(){

    // return Get_servet_action(); from NetClient

    MessageFromServer message;
    message.type = player;

    return message;
}