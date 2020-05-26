#include <actionServer.h>

actionServer::actionServer (): myPosition(500.0,500.0), mySight({0, 0}, {0, 0}){}

void actionServer::sendActionMove(DirectionInterface direction){

    MoveInterface event(EventInterface::EventType::move, mySight, direction);

    //std::cout<<event.direction<<"\n";

    std::shared_ptr<EventInterface> ptr = std::make_shared<MoveInterface>(event);
    network.send_user_action(ptr);

}

void actionServer::sendActionBlink(){

    auto event = BlinkInterface(EventInterface::EventType::blink, mySight);
    std::shared_ptr<EventInterface> ptr = std::make_shared<BlinkInterface>(event);

    network.send_user_action(ptr);
}

void actionServer::sendActionShot(){

    auto event = ShotInterface(EventInterface::EventType::shot, mySight);
    std::shared_ptr<EventInterface> ptr = std::make_shared<ShotInterface>(event);

    network.send_user_action(ptr);
}


void actionServer::updatePosition(const std::vector<std::shared_ptr<ObjectInterface>> &objects){

    myPosition = objects[myId]->position;
    mySight.from = myPosition;
}

void actionServer::updateSight(sf::Vector2f mouse_world) {

    PointInterface mouse(mouse_world.x, mouse_world.y);
    mySight.to = mouse;
}

std::vector<std::shared_ptr<ObjectInterface>> actionServer::getMessage(){

    return network.get_server_message();
}

void actionServer::connectClient(){

    network.connect_to_server(addr_server, port); //from NetClient
    // myId = id от сетей
    myId = network.get_id();
}

void actionServer::closeConnectClient(){
    //функция разрыва соединения
}