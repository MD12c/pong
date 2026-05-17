#include"server.h"


Server::Server(int port) {
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
        std::cout << WSAGetLastError() << std::endl;
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    } else {
        std::cout << "Socket created successfully" << std::endl;
    }

    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    //serverAddr.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    int binderr = bind(socketID, (sockaddr*)&serverAddr, sizeof(serverAddr));

    if(binderr == SOCKET_ERROR) {
        std::cout << WSAGetLastError() << std::endl;
        closesocket(socketID);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket");
    } else {
        std::cout << "Socket bound successfully" << std::endl;
    }
}

Server::~Server() {
    closesocket(socketID);
    WSACleanup();
}

SOCKET Server::standby() {
    int listenerr = listen(socketID, 1);

    if(listenerr != 0) {
        std::cout << WSAGetLastError() << std::endl;
        closesocket(socketID);
        WSACleanup();
        throw std::runtime_error("Failed to listen");
    } else {
        std::cout << "listening" << std::endl;
    }


    SOCKET acceptSocket;
    acceptSocket = accept(socketID, NULL, NULL);

    if(acceptSocket == INVALID_SOCKET) {
        std::cout << WSAGetLastError() << std::endl;
        closesocket(socketID);
        WSACleanup();
        throw std::runtime_error("Failed to accept socket");
    } else {
        std::cout << "Created accept socket" << std::endl;
    }

    return acceptSocket;
}