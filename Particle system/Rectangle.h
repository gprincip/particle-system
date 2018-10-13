#pragma once

#include"Shader.h"
#include<vector>
#include<random>
#include<chrono>
#include<ft2build.h>
#include"GL\glfw3.h"
#include"GL\glm\common.hpp"
#include"GL\glm\gtc\matrix_transform.hpp"
#include "Sphere.h"
#include "Configuration.h"
#include FT_FREETYPE_H

class Rectangle
{

public:
	Rectangle() {}
	~Rectangle() {}
public:

	void Init();
	void Render(GLfloat aspect);
	void Shutdown();

private:
	void init_ParticleShader();
	void init_TextRenderingShader();
	void init_buffer();
	void init_vertexArray();
	void init_textBufferAndFreetype();
	void render_text(const char *text, float x, float y, float sx, float sy);
	void init_sphere();
	void init_lines();

private:
	Configuration config;

	//Buffers for sphere rendering
	GLuint sphere_vao;
	GLuint sphere_vbo;

	GLint sphere_program;
	GLint sphere_compute_program;
	GLuint sphere_position_buffer;
	GLuint sphere_tbo;
	
	GLuint sphere_storage_buffer_object;

	float *sphere_vertices;
	GLuint sphere_centers_buffer;

	std::vector<Sphere> spheres;
	int nFloats; //number of floats in sphere vbo

	GLint line_program;
	GLuint line_vao;
	GLuint line_vbo;
	GLint lineIndex;

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

	GLuint  render_vao;

};
