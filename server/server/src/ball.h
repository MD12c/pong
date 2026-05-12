#pragma once

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

extern GLfloat ballR;
extern GLfloat ball[20];

namespace Ball {
    extern glm::mat4 model;

    struct Physics {
        float v = 1.0f;
        int ratio = 0;
        float x = 0.0f, y = 0.0f;  
    };

    extern Physics ball;
    void initialize();
    glm::mat4 translate(GLFWwindow* window, float dT);
    glm::vec3 getPosition();
};