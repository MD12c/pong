#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include<iostream>

class Client {
public:

    SOCKET socketID = INVALID_SOCKET;
    Client();
    ~Client();

    void connect();
};