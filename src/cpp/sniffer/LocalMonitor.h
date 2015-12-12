//
// Created by grg on 12/12/15.
//

#ifndef HOME_SECURITY_SNIFFER_H
#define HOME_SECURITY_SNIFFER_H

#include "ConnectionMap.h"

class LocalMonitor {
private:
    ConnectionMap connection_map;
public:
    void add_packet_data(const Tins::IP *ip, const Tins::Packet& packet);

    void report_connections();
};


#endif //HOME_SECURITY_SNIFFER_H
