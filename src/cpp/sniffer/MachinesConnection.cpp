//
// Created by grg on 07/12/15.
//

#include <iostream>
#include "MachinesConnection.h"

void MachinesConnection::accumulate_packet(const Tins::IP *ip, const Tins::Packet &packet) {
    bool is_add = false;
    if (timestamps.size() == 0) {
        is_add = true;
    } else {
        Tins::Timestamp &last_timestamp = timestamps[timestamps.size() - 1];
        if (packet.timestamp().seconds() - last_timestamp.seconds()  > 10) {
            is_add = true;
        }
    }

    if (is_add) {
        timestamps.push_back(packet.timestamp());
    }
}
