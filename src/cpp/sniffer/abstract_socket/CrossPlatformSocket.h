//
// Created by grg on 12/12/15.
//

#ifndef HOME_SECURITY_CROSSPLATFORMSOCKET_H
#define HOME_SECURITY_CROSSPLATFORMSOCKET_H


#include <stdint.h>
#include <stddef.h>
#include <string>

class CrossPlatformSocket {
private:
    uint64_t socket_desc;
public:
    bool init();
    bool connect_server(const std::string &remote_addr, uint16_t remote_port);
    bool send(const uint8_t * data, size_t data_size);
    bool recv(char *data, size_t data_size);
};


#endif //HOME_SECURITY_CROSSPLATFORMSOCKET_H
