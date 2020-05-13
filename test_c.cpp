//
// Created by Vladislav Shushpanov on 11.05.2020.
//
#include <NetClient.h>


int main() {
    NetClient net;
    net.connect_to_server("127.0.0.1", 8001);

   // std::vector<std::shared_ptr<ObjectInterface>> mes = net.get_server_message();
    auto move = MoveInterface(EventInterface::EventType::move, {{1, 1},{2, 2}}, Direction::DOWN);
    std::shared_ptr<EventInterface> ptr = std::make_shared<MoveInterface>(move);

    net.send_user_action(ptr);

    return 0;
};