#include <actionServer.h>


void actionServer::sendActionMove(Direction direction){

    MoveInterface event(static_cast<EventInterface::EventType>(EventInterface::EventType::move), mySight, direction);

    //std::cout<<event.direction<<"\n";

    // Send_action(event); from NetClient
}

void actionServer::sendActionBlink(){

    BlinkInterface event(static_cast<EventInterface::EventType>(EventInterface::EventType::move), mySight);

    //std::cout<<event.sight.to.x<<"\n";
    //std::cout<<event.sight.to.y<<"\n";

    // Send_action(event); from NetClient
}

void actionServer::updatePosition(){

    myPosition.x = 500;
    myPosition.y = 500;
}

void actionServer::updateSight(int x, int y){

/*
    Point mouse;
    mouse.x = x;
    mouse.y = y;

    myPosition.x = 500;
    myPosition.y = 500;

    mySight.from = myPosition;
    mySight.to = mouse;
*/
}

std::vector<std::shared_ptr<ObjectInterface>> actionServer::getMessage(){

    // return Get_servet_action(); from NetClient

    std::vector<std::shared_ptr<ObjectInterface>> vec;
/*
    ObjectInterface object;
    object.type = STATIC_OBJECT;
*/
    return vec;

}