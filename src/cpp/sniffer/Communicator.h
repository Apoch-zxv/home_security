//
// Created by grg on 12/12/15.
//

#ifndef HOME_SECURITY_COMMUNICATOR_H
#define HOME_SECURITY_COMMUNICATOR_H

#include <string>
#include <thread>
#include <tins/tins.h>
#include "abstract_socket/CrossPlatformSocket.h"

class Communicator {
private:
    Tins::IP::address_type server_address;
    uint16_t server_port;

    CrossPlatformSocket crossPlatformSocket;

public:
    void init(const std::string &server_address, uint16_t server_port);

    bool send(const uint8_t* data, size_t data_size);

    void incomming_command();

    void reconnect();
};


#endif //HOME_SECURITY_COMMUNICATOR_H
