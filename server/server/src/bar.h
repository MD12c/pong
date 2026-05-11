#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Bar {
private:
    int m_goUpKey;
    int m_goDownKey;
    glm::mat4 m_model = glm::mat4(1.0f);
public:
    Bar(int goUpKey, int goDownKey);
    ~Bar();

    glm::mat4 translate();
};
