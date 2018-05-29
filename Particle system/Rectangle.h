#pragma once

#include"Shader.h"
#include<vector>
#include<random>
#include<chrono>
#include<ft2build.h>
#include"GL\glfw3.h"
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


private:
	void init_ParticleShader();
	void init_TextRenderingShader();
	void init_buffer();
	void init_vertexArray();
	void init_textBufferAndFreetype();
	void render_text(const char *text, float x, float y, float sx, float sy);

private:

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
public:
	GLfloat rotationAngle;
	
	// Posisition and velocity buffers
	union
	{
		struct
		{
			GLuint position_buffer;
			GLuint velocity_buffer;
		};
		GLuint buffers[2];
	};

	// TBOs
	union
	{
		struct
		{
			GLuint position_tbo;
			GLuint velocity_tbo;
		};
		GLuint tbos[2];
	};

	// Attractor UBO
	GLuint  attractor_buffer;

	// Program, vao and vbo to render a full screen quad
	GLuint  render_vao;
	GLuint  render_vbo;
};


