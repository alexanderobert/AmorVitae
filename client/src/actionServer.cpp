#include <actionServer.h>

actionServer::actionServer (): myPosition(500.0,500.0), mySight({0, 0}, {0, 0}){}

void actionServer::sendActionMove(DirectionInterface direction){

    MoveInterface event(EventInterface::EventType::move, mySight, direction);

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

    network.connect_to_server(addr_server, port);
    myId = network.get_id();
}

void actionServer::closeConnectClient(){
    //функция разрыва соединения
}

bool actionServer::checkWinner(const std::vector<std::shared_ptr<ObjectInterface>> &objects){
    std::map<ObjectInterface::Type, std::vector<std::shared_ptr<ObjectInterface>>> group;

    for (const std::shared_ptr<ObjectInterface> &obj : objects) {
        group[obj->type].push_back(obj);
    }

    int pointOfWinner = 0;
    int idOfWinner = 0;
    std::vector<MapInterface> mapData;

    for (std::shared_ptr<ObjectInterface> &obj : group[ObjectInterface::Type::MAP_OBJECT]) {
        mapData.emplace_back(*std::static_pointer_cast<MapInterface>(obj));
    }

    for (auto point : mapData[0].players_pts){
        if(point.second > pointOfWinner) {
            pointOfWinner = point.second;
            idOfWinner = point.first;
        }
    }

    return idOfWinner == myId;

}