//
// Created by grg on 07/12/15.
//

#include "ConnectionMap.h"

#include <string>
#include <fstream>

using namespace std;
using namespace Tins;

void ConnectionMap::add_packet_data(const Tins::IP *ip, const Tins::Packet &packet) {
    lock.lock();
    string protocol_name;
    IP::address_type source = ip->src_addr();
    IP::address_type dest = ip->dst_addr();
    uint16_t src_port;
    uint16_t dst_port;

    const TCP* tcp = packet.pdu()->find_pdu<TCP>();
    if (tcp != nullptr) {
        src_port = tcp->sport();
        dst_port = tcp->dport();
        protocol_name = "TCP";
    }

    const UDP* udp = packet.pdu()->find_pdu<UDP>();
    if (udp != nullptr) {
        src_port = udp->sport();
        dst_port = udp->dport();
        protocol_name = "UDP";
    }

    string key = buildConnectionKey(ip, protocol_name, src_port, dst_port, tcp, udp);

    connections[key].accumulate_packet(ip, packet);

    lock.unlock();
}

string ConnectionMap::buildConnectionKey(const IP *ip, const string &protocol_name, uint16_t src_port,
                                         uint16_t dst_port, const TCP *tcp, const UDP *udp) const {
    string key;
    if ((tcp != nullptr) || (udp != nullptr)) {
        string smaller_ip, bigger_ip;
        string smaller_port, bigger_port;
        if (ip->src_addr() < ip->dst_addr()) {
            smaller_ip = ip->src_addr().to_string();
            bigger_ip = ip->dst_addr().to_string();

            smaller_port = to_string(src_port);
            bigger_port = to_string(dst_port);
        } else if (ip->src_addr() > ip->dst_addr()) {
            bigger_ip = ip->src_addr().to_string();
            smaller_ip = ip->dst_addr().to_string();

            bigger_port = to_string(src_port);
            smaller_port = to_string(dst_port);
        } else {
            if (src_port < dst_port) {
                smaller_ip = ip->src_addr().to_string();
                bigger_ip = ip->dst_addr().to_string();

                smaller_port = to_string(src_port);
                bigger_port = to_string(dst_port);
            } else {
                bigger_ip = ip->src_addr().to_string();
                smaller_ip = ip->dst_addr().to_string();

                bigger_port = to_string(src_port);
                smaller_port = to_string(dst_port);
            }
        }

        key = protocol_name + ":" + smaller_ip + string(":") + smaller_port + ":" +
                bigger_ip + ":" + bigger_port;
    }
    return key;
}

ConnectionMap ConnectionMap::copy_wipe() {
    lock.lock();
    ConnectionMap copy(*this);
    this->connections.clear();
    lock.unlock();
    return copy;
}

ConnectionMap::ConnectionMap() {
}

std::set<std::string> ConnectionMap::get_keys() const {
    set<string> connection_key_set;
    for ( const auto &connection : connections ) {
        connection_key_set.insert(connection.first);
    }
    return connection_key_set;
}
