#pragma once

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

GLfloat ballR = 0.1f;

extern GLfloat ball[20] = {
	-ballR/2, ballR/2, 0.0f,   0.0f, 1.0f,
	 ballR/2, ballR/2, 0.0f,   1.0f, 1.0f,
	-ballR/2,-ballR/2, 0.0f,   0.0f, 0.0f,
	 ballR/2,-ballR/2, 0.0f,   1.0f, 0.0f
};

namespace Ball {
    glm::mat4 model = glm::mat4(1.0f);
    float v = 0.0002f;
    int ratio = rand() % 101;
    float x = v / ratio;
    float y = v - x;
    
    glm::mat4 translate(GLFWwindow* window) {
        //if(model[3][1] + ballR/2 <= 1 && model[3][1] + ballR/2 >= -1){
    	    model = glm::translate(model, glm::vec3(0.0f, 0.0005f, 0.0f));
        //}
        return model;
    }
};