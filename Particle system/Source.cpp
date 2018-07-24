
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
Rectangle rect;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(1600, 900, "Window", NULL, NULL);
	
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	
	//Hide mouse pointer, and capture it (keep it inside the window)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	
	rect.window = window;
	rect.Init();

	glfwSetCursorPosCallback(window, mouse_callback);

	while (!glfwWindowShouldClose(window)) {

		//Make offsets 0 if mouse is not moving
		rect.xOffset = 0.0;
		rect.yOffset = 0.0;
		//Check for events
		glfwPollEvents();
		
		//Kada se renderuju sfere, iskljuci blendovanje i ukljuci depth test

		//glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		//glDisable(GL_BLEND);

		float aspect = (float)screenWidth / (float)screenHeight;
		rect.Render(aspect);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (rect.firstMouse) {
		rect.lastX = xpos;
		rect.lastY = ypos;
		rect.firstMouse = false;
	}

	float sensitivity = 0.1;

	rect.xOffset = sensitivity * (xpos - rect.lastX);
	rect.yOffset = sensitivity * (rect.lastY - ypos);

	rect.lastX = xpos; 
	rect.lastY = ypos;

}