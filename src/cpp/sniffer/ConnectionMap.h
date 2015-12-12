//
// Created by grg on 07/12/15.
//

#ifndef HOME_SECURITY_CONNECTIONMAP_H
#define HOME_SECURITY_CONNECTIONMAP_H

#include <map>
#include <set>
#include <string>
#include <tins/tins.h>
#include "MachinesConnection.h"
#include <mutex>

class ConnectionMap {
private:
    std::mutex lock;
    std::map<std::string, MachinesConnection> connections;

    std::string buildConnectionKey(const Tins::IP *ip, const std::string &protocol_name, uint16_t src_port,
                                   uint16_t dst_port, const Tins::TCP *tcp, const Tins::UDP *udp) const;
public:

    ConnectionMap();

    ConnectionMap(const ConnectionMap& copy) : connections(copy.connections) {};

    void add_packet_data(const Tins::IP *ip, const Tins::Packet& packet);

    ConnectionMap copy_wipe();

    std::set<std::string> get_keys() const;
};


#endif //HOME_SECURITY_CONNECTIONMAP_H
