//
// Created by Vladislav Shushpanov on 11.05.2020.
//
#include <NetClient.h>


int main() {
    NetClient net;
    net.connect_to_server("127.0.0.1", 8001);

    auto move = BlinkInterface(EventInterface::EventType::blink, {{1, 1},{2, 2}});
    std::shared_ptr<EventInterface> ptr = std::make_shared<BlinkInterface>(move);

    while(true) {
        net.send_user_action(ptr);
        auto mes = net.get_server_message();
        for(const auto& c: mes) {
            std::cout<<c->position.x<<" "<<c->position.y<<std::endl;
        }
        usleep(10000);
    }
    return 0;
};