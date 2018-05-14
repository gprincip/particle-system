#pragma once

#include"Shader.h"
#include<vector>

enum
{
	PARTICLE_GROUP_SIZE = 128,
	PARTICLE_GROUP_COUNT = 8000,
	PARTICLE_COUNT = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT),
	MAX_ATTRACTORS = 64
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
	void init_shader();
	void init_buffer();
	void init_vertexArray();


private:

	GLuint vao;
	GLuint vao2; //za linije
	GLuint vbo;
	GLuint vbo2; //za linije
	GLint program;
	Shader shader;

	GLuint  output_image;
	// Member variables
	GLuint  compute_prog;
	GLuint  render_prog;
	// Compute program
	GLint   dt_location;

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

	// Mass of the attractors
	float attractor_masses[MAX_ATTRACTORS];
};


