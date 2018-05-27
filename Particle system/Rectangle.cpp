
#include "Rectangle.h"
#include"vmath.h"
#include<Windows.h>

static inline float random_float()
{
	float res;
	unsigned int tmp;
	static unsigned int seed = 0xFFFF0C59;

	seed *= 16807;

	tmp = seed ^ (seed >> 4) ^ (seed << 15);

	*((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

	return (res - 1.0f);
}

static vmath::vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
{
	vmath::vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
	randomvec = normalize(randomvec);
	randomvec *= (random_float() * (maxmag - minmag) + minmag);

	return randomvec;
}



static inline float random_float_in_range(float min, float max) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::random_device randomDevice; 
	std::default_random_engine generator(seed);

	std::uniform_real_distribution<double> distribution(min, max);

	return distribution(generator);
	
}

static double distance(vmath::vec4 a, vmath::vec4 b) {

	return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));

}

void Rectangle::Init()
{
	init_buffer();
	init_vertexArray();
	
	init_ParticleShader();
	init_TextRenderingShader();
	init_textBufferAndFreetype();
	rotationAngle = 0.0f;

}

void Rectangle::Render(GLfloat aspect)
{
	
	//init_particleShader() will also use particle shader
	//init_ParticleShader();
	//glBindBuffer(GL_ARRAY_BUFFER, position_buffer);

	// Activate the compute program and bind the position and velocity buffers
	// Preko tekstura povezujemo bafer i sejder, da sejder moze da cita i upisuje u bafer
	//glUseProgram(compute_prog);
	//glBindImageTexture(0, velocity_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	//glBindImageTexture(1, position_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	// Set delta time
	//glUniform1f(dt_location, delta_time);
	// Dispatch
	//glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);

	//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	
	if (rotationAngle >= 360.0) rotationAngle = 0.0;

	
	GLfloat black[4] = { 1, 1, 1, 1 };
	glUniform4fv(uniform_color, 1, black);

	float sx = 2.0 / 1600;
	float sy = 2.0 / 900;

	vmath::mat4 mvp = vmath::perspective(45.0f, aspect, 0.1f, 1000.0f) *
		vmath::translate(0.0f, 0.0f, -40.0f) *
		vmath::rotate(/*time * 1000.0f*/ /*rotationAngle+=0.2*/ 0.0f /*150.0f*/ , vmath::vec3(0.0f, 1.0f, 0.0f));

	// Clear, select the rendering program and draw a full screen quad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);	
	//glUseProgram(render_prog);
	glUniformMatrix4fv(0, 1, GL_FALSE, mvp);
	
	//glBindVertexArray(render_vao);
	glEnable(GL_BLEND);
	//this kind of blending must be used for freetype text rendering
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
		//-1 + 8 * sx, 1 - 50 * sy, sx, sy);
	//glPointSize(5.0f);
	//init_buffer();
	//init_vertexArray();
	//init_ParticleShader();
	
	//glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);

	
	glUseProgram(text_render_prog);
	render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
		-1 + 8 * sx, 1 - 50 * sy, sx, sy);

}

void Rectangle::Shutdown()
{
	glUseProgram(0);
	glDeleteProgram(compute_prog);
	glDeleteProgram(render_prog);
	//glDeleteProgram(text_rendering_prog);
	glDeleteVertexArrays(1, &render_vao);
	glDeleteVertexArrays(1, &fontVao);
}


void Rectangle::init_ParticleShader()
{
	shader.setUpShader("core.vs", "core.frag", "core.comp");
	shader.use();
	render_prog = shader.programNonComputeShader;

	compute_prog = shader.programComputeShader;
	dt_location = glGetUniformLocation(compute_prog, "dt");
}

void Rectangle::init_TextRenderingShader() {

	shader.setUpShader("fontVertexShader.vs", "fontFragmentShader.frag", "");
	text_render_prog= shader.programNonComputeShader;

	//CompShader.init();
	//CompShader.attach(GL_COMPUTE_SHADER, "simple.comp");
	//CompShader.link();
	//compute_prog = shader.programComputeShader;
	//dt_location = glGetUniformLocation(compute_prog, "dt");

}

void Rectangle::init_buffer()
{
	glGenVertexArrays(/*2*/ 1, &render_vao);
	glBindVertexArray(render_vao);

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(vmath::vec4), NULL, GL_DYNAMIC_COPY);

	vmath::vec4 * positions = (vmath::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER,
		0,
		PARTICLE_COUNT * sizeof(vmath::vec4),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
	
		/*float v1 = random_float_in_range(5.0, 5.3);
		float v2 = random_float_in_range(5.0, 5.3);
		float v3 = random_float_in_range(5.0, 5.3);*/

		positions[i] = vmath::vec4(random_vector(0.001f , 0.002f) /*vmath::vec3(v1,v2,v3)*/ , random_float());
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glGenTextures(2, tbos);

	for (int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_BUFFER, tbos[i]);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, buffers[i]);
	}

}

void Rectangle::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void Rectangle::init_textBufferAndFreetype() {

	attribute_coord = glGetUniformLocation(text_render_prog, "coord");
	uniform_tex = glGetUniformLocation(text_render_prog, "tex");
	uniform_color = glGetUniformLocation(text_render_prog, "color");

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(uniform_tex, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenVertexArrays(1, &fontVao);
	glBindVertexArray(fontVao);
	glGenBuffers(1, &fontVbo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, fontVbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	if (FT_Init_FreeType(&ft)) {
		cout << "Could not init freetype library\n" << endl;
	}

	if (FT_New_Face(ft, "FreeSans.ttf", 0, &face)) {
		cout << "Could not open font" << endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	g = face->glyph;
}

void Rectangle::render_text(const char *text, float x, float y, float sx, float sy) {
	const char *p;

	for (p = text; *p; p++) {
		if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			g->bitmap.width,
			g->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			g->bitmap.buffer
		);

		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2,     -y2    , 0, 0 },
			{ x2 + w, -y2    , 1, 0 },
			{ x2,     -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x / 64) * sx;
		y += (g->advance.y / 64) * sy;
	}

}