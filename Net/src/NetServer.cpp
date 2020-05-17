//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#include <NetServer.h>
using namespace boost::asio;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

std::vector<User> NetServer::accept_users(int players_count, const ObjectManager& objm) {
    ip::tcp::acceptor acc(io_service, ip::tcp::endpoint(ip::tcp::v4(),8001));
    int player = 0;
    while (true) {
        if (player == players_count) {
            break;
        }
        boost::shared_ptr<boost::asio::ip::tcp::socket> user_socket(new ip::tcp::socket(io_service));
        users.emplace_back(1, user_socket);
        acc.accept(*users[player].sock);
        player++;
    }
    return users;
}

void NetServer::notify_all_users(std::map<int, std::shared_ptr<Object>>& object) {
    std::string buf = packet_manager.packet_handle_server(object);
    for (auto & item : users){
        item.sock->write_some(buffer(buf));
    }
}

std::shared_ptr<Event> NetServer::get_client_action(User& user) {
    ptree root;
    char buf[1024] = "";

    int size_buff = do_read_header(user);

    user.sock->read_some(buffer(buf,size_buff));

    std::cout<< buf <<std::endl;

    std::string json = std::string(buf);
    std::stringstream stream(json);

    read_json(stream, root);
    root.put("IDuser", user.get_username());
    return packet_manager.packet_adaptation_server(root);;
}

int NetServer::do_read_header(User& user) {
    char buf[1024] = "";
    user.sock->read_some(buffer(buf, 3));
    std::istringstream iss (buf, std::istringstream::in);
    int val;
    iss >> val;
    return val;
}