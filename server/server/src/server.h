#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>
#include "glad/glad.h"
// #include <thread>
// #include <chrono>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

struct GameStatus {
    glm::vec2 bar1Pos;
    glm::vec2 bar2Pos;
    glm::vec2 ballPos;
    int8_t gameState;
};

class Server {
public:
    SOCKET socketID = INVALID_SOCKET;
    Server(int port);
    ~Server();

    SOCKET standby();


    GameStatus getGameStatus(glm::vec2 bar1Pos, glm::vec2 bar2Pos, glm::vec2 ballPos, int8_t gameState);
};