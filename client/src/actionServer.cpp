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


