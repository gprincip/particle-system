#pragma once

#include"Shader.h"
#include<vector>
#include<random>
#include<chrono>
#include<ft2build.h>
#include"GL\glfw3.h"
#include"GL\glm\common.hpp"
#include"GL\glm\gtc\matrix_transform.hpp"
#include FT_FREETYPE_H

enum
{
	PARTICLE_GROUP_SIZE = 128,
	PARTICLE_GROUP_COUNT = 5000,
	PARTICLE_COUNT = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT),
};


class Rectangle
{

public:
	Rectangle() {}
	~Rectangle() {}
public:

	void Init();
	void Render(GLfloat aspect);
	void Shutdown();
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

private:
	void init_ParticleShader();
	void init_TextRenderingShader();
	void init_buffer();
	void init_vertexArray();
	void init_textBufferAndFreetype();
	void render_text(const char *text, float x, float y, float sx, float sy);
private:

	int width = 0, height = 0;

	GLuint vao;
	GLuint vbo;

	GLuint fontVao;
	GLuint fontVbo;

	GLint attribute_coord;

	GLuint tex; //Font texture
	GLint uniform_tex;
	GLint uniform_color;
	
	GLint program;
	Shader shader;

	GLuint  output_image;
	// Member variables
	GLuint compute_prog;
	GLuint render_prog;
	GLuint text_render_prog;
	// Compute program
	GLint   dt_location;

	FT_Library ft; //freeType library
	FT_Face face;
	FT_GlyphSlot g;

	float cameraSpeed = 0.7;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	int currentVectorField = 1;

public:
	GLfloat rotationAngle;
	GLFWwindow *window;

	//Last position of the mouse
	double lastX, lastY;
	double xOffset, yOffset;

	bool firstMouse = true;

	//Euler's angles
	float pitch = 0;
	float yaw = 0;

	// Posisition buffer
	GLuint position_buffer;

	// TBOs
	GLuint position_tbo;

	// Program, vao and vbo to render a full screen quad
	GLuint  render_vao;
	GLuint  render_vbo;
};


