//
// Created by Vladislav Shushpanov on 14.04.2020.
//

#ifndef NEW_USER_H
#define NEW_USER_H

#include <boost/asio.hpp>
#include <utility>



class User {
public:
    User(int ID, boost::shared_ptr<boost::asio::ip::tcp::socket> socket) {
        ID_user = ID;
        sock = std::move(socket);

    }
    ~User() = default;
    int get_username();
    bool is_connected() { return true;}

    boost::shared_ptr<boost::asio::ip::tcp::socket> sock;
private:
    int ID_user;
    bool status;
};



#endif //NEW_USER_H
