//
// Created by grg on 12/12/15.
//

#ifndef HOME_SECURITY_SNIFFER_H
#define HOME_SECURITY_SNIFFER_H

#include "ConnectionMap.h"
#include "Communicator.h"
#include <string>

class LocalMonitor {
private:
    ConnectionMap connection_map;
    Communicator communicator;

public:
    void start(const std::string &server_ip, uint16_t server_port);

    void add_packet_data(const Tins::IP *ip, const Tins::Packet& packet);

    void report_connections();
};


#endif //HOME_SECURITY_SNIFFER_H
