#include "main.h"
constexpr unsigned int width = 1500;
constexpr unsigned int height = 900;

int main()
{
	std::cout << "Hello CMake." << std::endl;
	
	// Name of the window, width & height of the window, background color RGB
	Window VIEWPORT("PONG SERVER", width, height, 0.1f, 0.1f, 0.1f);
	VIEWPORT.glfwSetup();
	Shader defShader("Assets/shaders/default.vert", "Assets/shaders/default.frag");
	defShader.Activate();
	
	//Imgui imgui(VIEWPORT.getWindow());
	//imgui.CreateContext();

// Server Connections
#pragma region
	try {
		Server server(55555);
		SOCKET socketSpeaking = server.standby();

		char recvBuffer[15] = {};
		int recvByteCount = recv(socketSpeaking, recvBuffer, sizeof(recvBuffer), 0);

		if(recvByteCount == 0) {
			std::cout << "No bytes recieved" << WSAGetLastError() << std::endl;
		} else {
			std::cout << "Bytes are recieved: " << recvByteCount << std::endl;
			std::cout << recvBuffer << std::endl;
		}

	}
	catch(const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
#pragma endregion

// Bar1
#pragma region
	Bar bar1(GLFW_KEY_W, GLFW_KEY_S, 1);
	VAO bar1VAO;
	bar1VAO.Bind();
	VBO bar1VBO(bar, sizeof(bar));
	bar1VBO.Bind();
	bar1VAO.LinkAttrib(bar1VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	bar1VAO.LinkAttrib(bar1VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
	EBO bar1EBO(indices, sizeof(indices));
	bar1EBO.Bind();

	Texture bar1Text("Assets/Textures/P1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	bar1Text.Bind();
	bar1Text.texUnit(defShader, "tex0", 0);
	bar1Text.Unbind(); bar1EBO.Unbind(); bar1VBO.Unbind(); bar1VAO.Unbind();
#pragma endregion

// Bar2
#pragma region
	Bar bar2(GLFW_KEY_P, GLFW_KEY_L, 2);
	VAO bar2VAO;
	bar2VAO.Bind();
	VBO bar2VBO(bar, sizeof(bar));
	bar2VBO.Bind();
	bar2VAO.LinkAttrib(bar2VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	bar2VAO.LinkAttrib(bar2VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
	EBO bar2EBO(indices, sizeof(indices));
	bar2EBO.Bind();
	
	Texture bar2Text("Assets/Textures/P2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	bar2Text.Bind();
	bar2Text.texUnit(defShader, "tex0", 0);
	bar2Text.Unbind(); bar2EBO.Unbind(); bar2VBO.Unbind(); bar2VAO.Unbind();
#pragma endregion

// Ball
#pragma region
	srand(time(0));
	Ball::initialize();
	VAO ballVAO;
	ballVAO.Bind();
	VBO ballVBO(ball, sizeof(ball));
	ballVBO.Bind();
	ballVAO.LinkAttrib(ballVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	ballVAO.LinkAttrib(ballVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
	EBO ballEBO(indices, sizeof(indices));
	ballEBO.Bind();
	
	Texture ballText("Assets/Textures/ball.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	ballText.Bind();
	ballText.texUnit(defShader, "tex0", 0);
	ballText.Unbind(); ballEBO.Unbind(); ballVBO.Unbind(); ballVAO.Unbind();
#pragma endregion
	
// Shader pointers
#pragma region
	GLint modelLoc = glGetUniformLocation(defShader.ID, "translated");
	GLint colorLoc = glGetUniformLocation(defShader.ID, "Color");
	glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
#pragma endregion
	
	float dT = 0.0f;
	float lastFrame = 0.0f;
	glfwSetTime(0.0f);

	while (!glfwWindowShouldClose(VIEWPORT.getWindow())) {
		VIEWPORT.glClearCurrentColor();
		//imgui.ShowDockSpace();
		glClear(GL_COLOR_BUFFER_BIT);

		float crntFrame = static_cast<float>(glfwGetTime());
    	dT = crntFrame - lastFrame;
	    lastFrame = crntFrame;

	// visuals
	#pragma region
		bar1VAO.Bind(); bar1VBO.Bind(); bar1EBO.Bind(); bar1Text.Bind();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bar1.translate(VIEWPORT.getWindow(), width, height, dT)));
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		bar1Text.Unbind(); bar1EBO.Unbind(); bar1VBO.Unbind(); bar1VAO.Unbind();

		bar2VAO.Bind(); bar2VBO.Bind(); bar2EBO.Bind(); bar2Text.Bind();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bar2.translate(VIEWPORT.getWindow(), width, height, dT)));
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		bar2Text.Unbind(); bar2EBO.Unbind(); bar2VBO.Unbind(); bar2VAO.Unbind();

		ballVAO.Bind(); ballVBO.Bind(); ballEBO.Bind(); ballText.Bind();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Ball::translate(VIEWPORT.getWindow(), dT)));
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		ballText.Unbind(); ballEBO.Unbind(); ballVBO.Unbind(); ballVAO.Unbind();
	#pragma endregion

	// Collision Physics
	#pragma region
		glm::vec2 bar1Pos = bar1.getPosition();
		glm::vec2 bar2Pos = bar2.getPosition();
		glm::vec2 ballPos = Ball::getPosition();

        if(Ball::model[3][0] + ballD/2 < -1 || Ball::model[3][0] - ballD/2 > 1) {
			std::cout << "\nGame over" << std::endl;
			break;
		}

		// outside x
		if(bar1Pos[0] + barW/2 > ballPos[0] - ballD/2) {
			if(!((bar1Pos[1] - barH/2 > ballPos[1]) || (bar1Pos[1] + barH/2 < ballPos[1]))) {
				Ball::ball.x = std::abs(Ball::ball.x) * 1.0f;
				Ball::model[3][0] = -1 + barW + ballD/2;
			}
		}
		
		if(bar2Pos[0] - barW/2 < ballPos[0] + ballD/2) {
			if(!((bar2Pos[1] - barH/2 > ballPos[1]) || (bar2Pos[1] + barH/2 < ballPos[1]))) {
				Ball::ball.x = -std::abs(Ball::ball.x) * 1.0f;
				Ball::model[3][0] = 1 - barW - ballD/2;
			}
		}
	#pragma endregion

		//ImGui::Begin("Template");
			//ImGui::ShowDemoWindow();
		//ImGui::End();
		//imgui.RenderDockSpace();
		glfwSwapBuffers(VIEWPORT.getWindow());
		glfwPollEvents();
	}

// Cleanup
#pragma region
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();
	defShader.Delete();
	bar1Text.Delete();
	bar1EBO.Delete();
	bar1VBO.Delete();
	bar1VAO.Delete();

	bar2Text.Delete();
	bar2EBO.Delete();
	bar2VBO.Delete();
	bar2VAO.Delete();

	ballText.Delete();
	ballEBO.Delete();
	ballVBO.Delete();
	ballVAO.Delete();
#pragma endregion

	return 0;
}
