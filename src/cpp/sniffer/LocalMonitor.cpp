//
// Created by grg on 12/12/15.
//

#include "LocalMonitor.h"

void LocalMonitor::add_packet_data(const Tins::IP *ip, const Tins::Packet &packet) {
    connection_map.add_packet_data(ip, packet);
}

void LocalMonitor::report_connections() {
    const ConnectionMap &copy = connection_map.copy_wipe();
    copy.get_keys();
}
