#include"client.h"

Client::Client() {
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if(wsaerr != 0) {
        throw std::runtime_error("Failed to initialize Winsock");
    } else {
        std::cout << "Winsock initialized successfully" << std::endl;
    }

    socketID = socket(AF_INET, SOCK_STREAM, 0);

    if(socketID == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    } else {
        std::cout << "Socket created successfully" << std::endl;
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(8080),
    };

    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
}

Client::~Client() {
    closesocket(socketID);
    WSACleanup();
}

void Client::connect() {
    // Connection implementation
}