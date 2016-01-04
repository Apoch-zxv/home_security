#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include "LocalMonitor.h"
#include <tins/tins.h>

using namespace std;
using namespace Tins;

LocalMonitor sniffer;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void report_connections() {
    cout << "Starting reported thread" << endl;
    while (true) {
        sniffer.report_connections();
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}
#pragma clang diagnostic pop

bool capture_loop(Packet& packet) {
    const IP *ip = packet.pdu()->find_pdu<IP>();
    if (ip != nullptr) {
        sniffer.add_packet_data(ip, packet);
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "usage: " << argv[0] << " interface" << endl;
        return 1;
    }

    sniffer.start("127.0.0.1", 5000);

    std::thread reporter(report_connections);

    Sniffer sniffer(argv[1], Sniffer::PROMISC);
    sniffer.sniff_loop(capture_loop);
    reporter.join();
    return 0;
}