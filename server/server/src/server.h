#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include<iostream>
// #include <thread>
// #include <chrono>

class Server {
public:

    SOCKET socketID = INVALID_SOCKET;
    Server();
    ~Server();

    SOCKET standby();
};