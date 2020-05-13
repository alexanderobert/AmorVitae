//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#include "NetClient.h"

using namespace boost::asio;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;



void NetClient::connect_to_server(std::string addr_server, int port) {
    ip::tcp::endpoint ep( ip::address::from_string(addr_server), port);
    boost::shared_ptr<boost::asio::ip::tcp::socket> sock(new ip::tcp::socket(io_service));
    socket_ptr = sock;
    sock->connect(ep);
}


std::vector<std::shared_ptr<ObjectInterface>> NetClient::get_server_message() {
    char buf[1024] = "";
    ptree root;

    socket_ptr->read_some(buffer(buf));

    std::string json = std::string(buf);

    std::stringstream stream(json);
    read_json(stream, root);

    return packet_manager.packet_adaptation_client(root);
}



void NetClient::send_user_action(std::shared_ptr<EventInterface>& event) {

    std::string buf = packet_manager.packet_handle_client(event);
    do_write_header(buf.size());
    socket_ptr->write_some(buffer(buf));
}

void NetClient::do_write_header(int size) {
    char buf[1];
    buf[0] = static_cast<char>(size);
    socket_ptr->write_some(buffer(buf));

}

