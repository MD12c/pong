#include "bar.h"

GLfloat barH = 0.5f;
GLfloat barW = 0.05f;
GLfloat bar[20] = {
	-barW/2, barH/2, 0.0f,   0.0f, 1.0f,
	 barW/2, barH/2, 0.0f,   1.0f, 1.0f,
	-barW/2,-barH/2, 0.0f,   0.0f, 0.0f,
	 barW/2,-barH/2, 0.0f,   1.0f, 0.0f
};
GLuint indices [6] = {
	0, 1, 2,
	1, 3, 2
};

Bar::Bar(int goUpKey, int goDownKey, int ID) : 
    m_goUpKey(goUpKey), 
    m_goDownKey(goDownKey),
    m_ID(ID)
{
if(m_ID == 1)
    m_model = glm::translate(m_model, glm::vec3(-1 + barW/2, 0.0f, 0.0f));
if(m_ID == 2)
    m_model = glm::translate(m_model, glm::vec3(1 - barW/2, 0.0f, 0.0f));

};

glm::mat4 Bar::translate(GLFWwindow* window, unsigned int width, unsigned int height) {
    if(glfwGetKey(window, m_goUpKey) == GLFW_PRESS && m_model[3][1] + barH/2 <= 1){
    	m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0005f, 0.0f));
    }
    if(glfwGetKey(window, m_goDownKey) == GLFW_PRESS && m_model[3][1] - barH/2 >= -1){
    	m_model = glm::translate(m_model, glm::vec3(0.0f, -0.0005f, 0.0f));
    }
    return m_model;
}

glm::vec3 Bar::getPosition() {
    return glm::vec3(m_model[3][0], m_model[3][1], 0.0f);
}

Bar::~Bar(){};
