#include"ball.h"

GLfloat ballR = 0.1f;

GLfloat ball[20] = {
	-ballR/2, ballR/2, 0.0f,   0.0f, 1.0f,
	 ballR/2, ballR/2, 0.0f,   1.0f, 1.0f,
	-ballR/2,-ballR/2, 0.0f,   0.0f, 0.0f,
	 ballR/2,-ballR/2, 0.0f,   1.0f, 0.0f
};

namespace Ball {
    glm::mat4 model = glm::mat4(1.0f);

    Physics ball;
    
    void initialize() {
        ball.ratio = rand() % 101;
        ball.x = (ball.v * ball.ratio) / 100;
        ball.y = ball.v - ball.x;
        std::cout << ball.ratio;
    }
    
    glm::mat4 translate(GLFWwindow* window) {
        if(model[3][0] + ballR/2 < -1 || model[3][0] - ballR/2 > 1){
            // Game over
        }
        if(model[3][1] + ballR/2 <= 1 && model[3][1] - ballR/2 >= -1){
    	    model = glm::translate(model, glm::vec3(ball.x, ball.y, 0.0f));
        } else {
            ball.y = -ball.y;
    	    model = glm::translate(model, glm::vec3(ball.x, ball.y, 0.0f));
        }
        return model;
    }

    glm::vec3 getPosition() {
        return glm::vec3(model[3][0], model[3][1], 0.0f);
    }
};