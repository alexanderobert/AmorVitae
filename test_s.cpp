//
// Created by Vladislav Shushpanov on 11.05.2020.
//
#include <NetServer.h>
int main() {
    NetServer net(8001);
    std::vector<User> users = net.accept_users(1);


    auto pl = Player(1, {50, 50});
    std::shared_ptr<Object> ptr = std::make_shared<Player>(pl);
    std::map<int, std::shared_ptr<Object>> m = {{0,ptr}};

    net.notify_all_users(m);
    std::shared_ptr<Event> event;
    for (auto& user : users) {
        event = net.get_client_action(user);
    }

    return 0;
};