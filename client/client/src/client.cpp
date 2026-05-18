#include"client.h"

Client::Client() {
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if(wsaerr != 0) {
        std::cout << WSAGetLastError() << std::endl;
        throw std::runtime_error("Failed to initialize Winsock");
    } else {
        std::cout << "Winsock initialized successfully" << std::endl;
    }

    socketID = socket(AF_INET, SOCK_STREAM, 0);

    if(socketID == INVALID_SOCKET) {
        std::cout << WSAGetLastError() << std::endl;
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    } else {
        std::cout << "Socket created successfully" << std::endl;
    }
}

Client::~Client() {
    closesocket(socketID);
    WSACleanup();
}

void Client::search(bool local) {
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &clientAddr.sin_addr);
    clientAddr.sin_port = htons(55555);
    int connecterr = connect(socketID, (SOCKADDR*)&clientAddr, sizeof(clientAddr));

    if(connecterr != 0) {
        std::cout << WSAGetLastError() << std::endl;
        closesocket(socketID);
        WSACleanup();
        throw std::runtime_error("Failed to connect socket");
    } else {
        std::cout << "Connected" << std::endl;
    }
}

