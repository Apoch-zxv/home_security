//
// Created by grg on 12/12/15.
//

#ifndef HOME_SECURITY_COMMUNICATOR_H
#define HOME_SECURITY_COMMUNICATOR_H

#include <string>
#include <tins/tins.h>

class Communicator {
private:
    Tins::IP::address_type server_address;
    uint16_t server_port;

public:
    Communicator(const std::string &server_address, uint16_t server_port) : server_address(server_address),
                                                                                       server_port(server_port) { }

    void init();

    bool send(const uint8_t* data, size_t data_size);
};


#endif //HOME_SECURITY_COMMUNICATOR_H
