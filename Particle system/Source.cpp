
#include<iostream>

#include"GL\glew.h"
#include"GL/glfw3.h"
#include "Shader.h"
#include"Rectangle.h"
#include "GL\glm\glm.hpp"

#include<ft2build.h>
#include FT_FREETYPE_H

using namespace std;
int screenWidth, screenHeight;

void main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(1600, 900, "Window", NULL, NULL);
	
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	
	if (window == NULL) {
		cout << "Neuspesno pravljenje prozora" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		cout << "Neuspesna inicijalizacija glew-a" << endl;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	Rectangle rect;
	rect.Init();

	while (!glfwWindowShouldClose(window)) {

		//provera da li se desio neki dogadjaj (tastatura, mis..)
		glfwPollEvents();

		static const glm::vec4 bgColor(0.2f, 0.4f, 0.5f, 1.0f);
		glClearBufferfv(GL_COLOR, 0, &bgColor[0]);

		rect.Render(screenWidth / screenHeight);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

}