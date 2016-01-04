//
// Created by grg on 12/12/15.
//

#include "CrossPlatformSocket.h"

#ifdef __linux__
//linux code goes here
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#elif _WIN32
// windows code goes here
#endif

bool CrossPlatformSocket::init() {
#ifdef __linux__
    return (socket_desc = (uint64_t)socket(AF_INET, SOCK_STREAM, 0)) >= 0;
#elif _WIN32
    return false;
#endif
}

bool CrossPlatformSocket::connect_server(const std::string &remote_addr, uint16_t remote_port) {
#ifdef __linux__
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(remote_port);

    if(inet_pton(AF_INET, remote_addr.c_str(), &serv_addr.sin_addr)<=0) {
        return false;
    }

    if(connect((int)socket_desc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        return false;
    }

    return true;
#elif _WIN32
    return false;
#endif
}

bool CrossPlatformSocket::recv(char *data, size_t data_size) {
#ifdef __linux__
    ssize_t read_bytes = read((int)socket_desc, data, data_size);

    if (read_bytes < 0) {
        return false;
    } else {
        data[read_bytes] = 0;
        return true;
    }
#elif _WIN32
    return false;
#endif
}

bool CrossPlatformSocket::send(const uint8_t *data, size_t data_size) {
#ifdef __linux__
    ssize_t read_bytes = write((int)socket_desc, data, data_size);

    return read_bytes >= 0;
#elif _WIN32
    return false;
#endif
}
