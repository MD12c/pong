#include "main.h"
constexpr unsigned int width = 1500;
constexpr unsigned int height = 900;

GLfloat barH = 0.4f;
GLfloat barW = 0.1f;
GLfloat bar[20] = {
	-barW/2, barH/2, 0.0f, 0.0f, 0.0f,
	 barW/2, barH/2, 0.0f, 0.0f, 1.0f,
	-barW/2,-barH/2, 0.0f, 1.0f, 0.0f,
	 barW/2,-barH/2, 0.0f, 1.0f, 1.0f
};
GLuint indices [6] = {
	0, 1, 2,
	1, 3, 2
};

int main()
{
	std::cout << "Hello CMake." << std::endl;

	// Name of the window, width & height of the window, background color RGB
	Window VIEWPORT("Template", width, height, 0.7f, 0.7f, 0.7f);
	VIEWPORT.glfwSetup();
	Shader defShader("Assets/shaders/default.vert", "Assets/shaders/default.frag");
	defShader.Activate();

	Imgui imgui(VIEWPORT.getWindow());
	imgui.CreateContext();

	VAO bar1VAO;
	bar1VAO.Bind();
	VBO bar1VBO(bar, sizeof(bar));
	bar1VBO.Bind();
	bar1VAO.LinkAttrib(bar1VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	bar1VAO.LinkAttrib(bar1VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
	EBO bar1EBO(indices, sizeof(indices));
	bar1EBO.Bind();

	Texture bar1Text("Assets/Textures/canion1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	bar1Text.Bind();
	bar1Text.texUnit(defShader, "tex0", 0);

	GLint modelLoc = glGetUniformLocation(defShader.ID, "translated");
	GLint colorLoc = glGetUniformLocation(defShader.ID, "Color");

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

	while (!glfwWindowShouldClose(VIEWPORT.getWindow())) {
		VIEWPORT.glClearCurrentColor();
		//imgui.ShowDockSpace();

		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		//ImGui::Begin("Template");
			//ImGui::ShowDemoWindow();
		//ImGui::End();
		//imgui.RenderDockSpace();
		glfwSwapBuffers(VIEWPORT.getWindow());
		glfwPollEvents();
	}

	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	defShader.Delete();
	bar1Text.Delete();
	bar1EBO.Delete();
	bar1VBO.Delete();
	bar1VAO.Delete();
	return 0;
}
