//
// Created by grg on 12/12/15.
//

#include <string>
#include "LocalMonitor.h"

using namespace std;

void LocalMonitor::add_packet_data(const Tins::IP *ip, const Tins::Packet &packet) {
    connection_map.add_packet_data(ip, packet);
}

void LocalMonitor::report_connections() {
    ConnectionMap copy = connection_map.copy_wipe();
    std::set<std::string> connection_keys = copy.get_keys();
    string res;
    for (const auto& key : connection_keys) {
        res += key + ",";
    }

    if (!communicator.send((const uint8_t *) res.c_str(), res.length())) {
        communicator.reconnect();
    }
}

void LocalMonitor::start(const std::string &server_ip, uint16_t server_port) {
    communicator.init(server_ip, server_port);
}
