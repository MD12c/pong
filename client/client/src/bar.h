#pragma once

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

extern GLfloat barH;
extern GLfloat barW;
extern GLfloat bar[20];
extern GLuint indices[6];

class Bar {
private:
    int m_goUpKey;
    int m_goDownKey;
    int m_ID;
public:
    glm::mat4 m_model = glm::mat4(1.0f);
    Bar(int goUpKey, int goDownKey, int ID);
    ~Bar();

    glm::mat4 translate(GLFWwindow* window, unsigned int width, unsigned int height, float dT);
    glm::vec2 getPosition();
};
