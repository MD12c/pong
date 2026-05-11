#include "bar.h"

Bar::Bar(int goUpKey, int goDownKey) : 
    m_goUpKey(goUpKey), 
    m_goDownKey(goDownKey)
{
};

glm::mat4 Bar::translate() {
	m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, 0.0f));
    return m_model;
}

Bar::~Bar(){};
