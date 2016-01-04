//
// Created by grg on 12/12/15.
//

#include <chrono>
#include <iostream>
#include "Communicator.h"

using namespace std;

void Communicator::init(const std::string &server_address, uint16_t server_port) {
    this->server_address = server_address;
    this->server_port = server_port;

    crossPlatformSocket.init();
    crossPlatformSocket.connect_server(this->server_address.to_string(), server_port);
    std::thread read_thread(&Communicator::incomming_command, this);
    read_thread.detach();
}

bool Communicator::send(const uint8_t *data, size_t data_size) {
    return crossPlatformSocket.send(data, data_size);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void Communicator::incomming_command() {
    cout << "Starting read thread" << endl;
    while (true) {
        char incomming_buffer[4096];
        if (!crossPlatformSocket.recv(incomming_buffer, sizeof(incomming_buffer))) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        } else {

        }
    }
}
#pragma clang diagnostic pop

void Communicator::reconnect() {
    crossPlatformSocket.init();
    crossPlatformSocket.connect_server(this->server_address.to_string(), server_port);
}
