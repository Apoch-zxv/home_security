//
// Created by grg on 07/12/15.
//

#ifndef HOME_SECURITY_CONNECTION_H
#define HOME_SECURITY_CONNECTION_H

#include <string>
#include <vector>
#include <fstream>
#include <tins/tins.h>

class MachinesConnection {
private:
    std::vector<Tins::Timestamp> timestamps;

public:
    MachinesConnection() { }

    void accumulate_packet(const Tins::IP *ip, const Tins::Packet& packet);
};


#endif //HOME_SECURITY_CONNECTION_H
