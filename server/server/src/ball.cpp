#include"ball.h"

GLfloat ballD = 0.1f;

GLfloat ball[20] = {
	-ballD/2, ballD/2, 0.0f,   0.0f, 1.0f,
	 ballD/2, ballD/2, 0.0f,   1.0f, 1.0f,
	-ballD/2,-ballD/2, 0.0f,   0.0f, 0.0f,
	 ballD/2,-ballD/2, 0.0f,   1.0f, 0.0f
};

namespace Ball {
    glm::mat4 model = glm::mat4(1.0f);

    Physics ball;
    
    void initialize() {
        ball.ratio = 100 - (rand() % 50);
        ball.x = (ball.v * ball.ratio) / 100;
        ball.y = ball.v - ball.x;
        std::cout << ball.ratio;
    }
    
    glm::mat4 translate(GLFWwindow* window, float dT) {
        float crntY = model[3][1];

        if(crntY + ballD/2 >= 1){
            ball.y = -std::abs(ball.y);
            model[3][1] = 1 - ballD/2;
        } else if(crntY - ballD/2 <= -1){
            ball.y = std::abs(ball.y);
            model[3][1] = -1 + ballD/2;
        }

        float moveX = ball.x * dT;
        float moveY = ball.y * dT;
        model = glm::translate(model, glm::vec3(moveX, moveY, 0.0f));
        return model;
    }
    

    glm::vec2 getPosition() {
        return glm::vec2(model[3][0], model[3][1]);
    }
};