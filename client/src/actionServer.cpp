#include <actionServer.h>

actionServer::actionServer (): myPosition(500.0,500.0), mySight({0, 0}, {0, 0}){}

void actionServer::sendActionMove(DirectionInterface direction){

    MoveInterface event(EventInterface::EventType::move, mySight, direction);

    //std::cout<<event.direction<<"\n";

    std::shared_ptr<EventInterface> ptr = std::make_shared<MoveInterface>(event);
    network.send_user_action(ptr);

}

void actionServer::sendActionBlink(){

    myPosition = mySight.to;

    auto event = BlinkInterface(EventInterface::EventType::blink, mySight);
    std::shared_ptr<EventInterface> ptr = std::make_shared<BlinkInterface>(event);

    network.send_user_action(ptr);
}

void actionServer::updatePosition(DirectionInterface direction){

    if(direction == up)
        myPosition.y = myPosition.y - 0.8;
    if(direction == down)
        myPosition.y = myPosition.y + 0.8;
    if(direction == left)
        myPosition.x = myPosition.x - 0.8;
    if(direction == right)
        myPosition.x = myPosition.x + 0.8;
}

void actionServer::updateSight(double x, double y) {

    PointInterface mouse(x, y);

    mySight.from = myPosition;
    mySight.to = mouse;

}

std::vector<std::shared_ptr<ObjectInterface>> actionServer::getMessage(){

    return network.get_server_message();
}

int actionServer::connectClient(){

    network.connect_to_server(addr_server, port); //from NetClient
    // myId = id от сетей
    myId = 1;
    return myId;
}

void actionServer::closeConnectClient(){
    //функция разрыва соединения
}