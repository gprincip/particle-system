
#include "Rectangle.h"
#include "Sphere.h"
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

static glm::vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
{
	glm::vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
	randomvec = normalize(randomvec);
	randomvec *= (random_float() * (maxmag - minmag) + minmag);

	return randomvec;
}



static inline float random_float_in_range(float min, float max) {

	float rndFlt = random_float();

	return min + (max - min) * rndFlt;

}

void Rectangle::Init()
{
	init_buffer();
	init_vertexArray();
	init_sphere();
	init_ParticleShader();
	init_lines();
	init_TextRenderingShader();
	init_textBufferAndFreetype();

	rotationAngle = 0.0f;
	glfwGetWindowSize(window, &width, &height);
	lastX = width / 2;
	lastY = height / 2;

	//Camera is positioned at the origin (0,0,0) and looks towards the negative z-axis
	cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//We initialize yaw at -90 so we are looking towards the negative z axis
	pitch = 0.0f;
	yaw = -90.0f;

	lineIndex = 0;
}

void Rectangle::Render(GLfloat aspect)
{

	/************************SETTINGS********************/
	glFinish();
	double startTime = glfwGetTime();


	if (rotationAngle >= 360.0) rotationAngle = 0.0;

	/******************CAMERA MOVEMENT******************/

	pitch += yOffset;
	yaw += xOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::mat4 projection = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -70.0f));

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) currentVectorField = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) currentVectorField = 2;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) currentVectorField = 3;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) currentVectorField = 4;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) currentVectorField = 5;

	glm::vec3 front;

	front[0] = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front[1] = sin(glm::radians(pitch));
	front[2] = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	/******************PARTICLES DRAWING*****************/

	glUseProgram(compute_prog);

	int currVF = glGetUniformLocation(compute_prog, "currentVectorField");
	glUniform1i(currVF, currentVectorField);

	//We are passing data to the shader using textures, here we are binding texture
	//at position 0, and reading it in shader via
	//layout (rgba32f, binding = 0) uniform imageBuffer position_buffer;

	glBindImageTexture(0, position_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	//Dispatch
	glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	glBindVertexArray(render_vao);
	glUseProgram(render_prog);

	int model_location = glGetUniformLocation(render_prog, "model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &model[0][0]);

	int view_location = glGetUniformLocation(render_prog, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);

	int projection_location = glGetUniformLocation(render_prog, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);

	//glPointSize(5.0f);
	//glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glBindVertexArray(0);

	/****************SPHERES DRAWING****************/
	//Disable blending so the spheres arent transparent

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(sphere_compute_program);
	glBindVertexArray(sphere_vao);

	int lineIndex_location = glGetUniformLocation(sphere_compute_program, "lineIndex");
	glUniform1i(lineIndex_location, lineIndex);
	lineIndex += 6*spheres.size();


	glDispatchCompute(36, 1, 1);

	glUseProgram(sphere_program);

	int viewPos_location = glGetUniformLocation(sphere_program, "cameraPos");
	glUniform3f(viewPos_location, cameraPos[0], cameraPos[1], cameraPos[2]);

	projection_location = glGetUniformLocation(sphere_program, "projection");
	view_location = glGetUniformLocation(sphere_program, "view");
	model_location = glGetUniformLocation(sphere_program, "model");

	glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &model[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, nFloats/9);
	
	/******************LINES DRAWING*****************/

	glUseProgram(line_program);
	glBindVertexArray(line_vao);

	projection_location = glGetUniformLocation(line_program, "projection");
	view_location = glGetUniformLocation(line_program, "view");
	model_location = glGetUniformLocation(line_program, "model");

	glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &model[0][0]);

	//glPointSize(5);
		
	glDrawArrays(GL_LINES, 0, 1024 * 1024);
	
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	/******************TEXT DRAWING*****************/

	glUseProgram(text_render_prog);
	glBindVertexArray(fontVao);

	float sx = 2.0 / 1600;
	float sy = 2.0 / 900;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat color[4];

	glFinish();
	double endTime = glfwGetTime();
	char deltaTime[50];
	sprintf_s(deltaTime, "ms ~ %.3f  Number of particles: %d", (endTime - startTime) * 1000, PARTICLE_COUNT);

	//Good fps - green, middle - purple, bad - red

	if ((endTime - startTime) * 1000 <= 10) {
		color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f; color[3] = 1.0f;
	}
	else if ((endTime - startTime) * 1000 > 10 && (endTime - startTime) * 1000 <= 20) {
		color[0] = 0.5f; color[1] = 0.0f; color[2] = 1.0f; color[3] = 1.0f;
	}
	else if ((endTime - startTime) * 1000 > 20) {
		color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
	}

	glUniform4fv(uniform_color, 1, color);

	render_text(deltaTime,
		-1 + 8 * sx, 1 - 30 * sy, sx, sy);

	//Sending delta time to shader so the movement of particles is less afected by framerate
	//glUseProgram(compute_prog);
	//glUniform1f(dt_location, ((endTime - startTime) * 1000));

}

void Rectangle::Shutdown()
{
	glUseProgram(0);
	glDeleteProgram(compute_prog);
	glDeleteProgram(render_prog);
	glDeleteProgram(text_render_prog);
	glDeleteVertexArrays(1, &render_vao);
	glDeleteVertexArrays(1, &fontVao);
}


void Rectangle::init_ParticleShader()
{
	shader.setUpShader("core.vs", "core.frag", "core.comp");
	render_prog = shader.programNonComputeShader;
	compute_prog = shader.programComputeShader;
	//dt_location = glGetUniformLocation(compute_prog, "dt");
}

void Rectangle::init_TextRenderingShader() {

	shader.setUpShader("fontVertexShader.vs", "fontFragmentShader.frag", "");
	text_render_prog= shader.programNonComputeShader;

}

void Rectangle::init_buffer()
{
	glGenVertexArrays(1, &render_vao);
	glBindVertexArray(render_vao);

	glGenBuffers(1, &position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(glm::vec4), NULL, GL_DYNAMIC_COPY);

	glm::vec4 * positions = (glm::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER,
		0,
		PARTICLE_COUNT * sizeof(glm::vec4),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
	
		float v1 = random_float_in_range(0, .01);
		float v2 = random_float_in_range(0, .01);
		float v3 = random_float_in_range(0, .01);

		positions[i] = glm::vec4(/*random_vector(0.0001 , 0.0002)*/ glm::vec3(v1,v2,v3) , random_float());
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glGenTextures(1, &position_tbo);
	glBindTexture(GL_TEXTURE_BUFFER, position_tbo);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, position_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Rectangle::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	glBindBuffer(GL_ARRAY_BUFFER, fontVbo);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	

	if (FT_Init_FreeType(&ft)) {
		cout << "Could not init freetype library\n" << endl;
	}

	if (FT_New_Face(ft, "FreeSans.ttf", 0, &face)) {
		cout << "Could not open font" << endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 18);

	g = face->glyph;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //unbind
}

void Rectangle::render_text(const char *text, float x, float y, float sx, float sy) {

	glBindVertexArray(fontVao);

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

		glBindBuffer(GL_ARRAY_BUFFER, fontVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		x += (g->advance.x / 64) * sx;
		y += (g->advance.y / 64) * sy;
	}

	glBindVertexArray(0);
	
}

void Rectangle::init_sphere() {

	shader.setUpShader("sphereShader.vs", "sphereShader.frag", "sphereShader.comp");
	sphere_program = shader.programNonComputeShader;
	sphere_compute_program = shader.programComputeShader;

	for (int i = 0; i < 3; i++) {
		spheres.push_back(*new Sphere());
	}

	for (int i = 0; i < spheres.size(); i++) {
		spheres[i].constructSphere(5.0f, 0.0f+5*i, 0.1f+i/2.0, 0.2f+ 3*i, 0.5f, 0.5f, 0.5f);
		spheres[i].subdivide(3);
	}

	//Data for vertices for all spheres collected inside one array
	std::vector<float> vertexData;

	std::vector<float> sphere_centers;
	for (int i = 0; i < spheres.size(); i++) {
		sphere_centers.push_back(spheres[i].x);
		sphere_centers.push_back(spheres[i].y);
		sphere_centers.push_back(spheres[i].z);
		
		float *arr = spheres[i].getFloats();

		for (int j = 0; j < spheres[i].getNumberOfFloats(); j++) {
			vertexData.push_back(arr[j]);
		}
	}

	nFloats = 0;

	for (int i = 0; i < spheres.size(); i++) {
		nFloats += spheres[i].getNumberOfFloats();
	}

	glUseProgram(sphere_compute_program);

	GLint vertices_per_sphere_location = glGetUniformLocation(sphere_compute_program, "verticesPerSphere");
	GLint verticesPerSphere = vertexData.size() / spheres.size();
	glUniform1i(vertices_per_sphere_location, verticesPerSphere);

	glUseProgram(0);

	glUseProgram(sphere_program);

	float lightPos[] = { -100.0f, 100.0f, 0.0f };

	int lightPos_locaton = glGetUniformLocation(sphere_program, "lightPos");
	glUniform3fv(lightPos_locaton ,1, &lightPos[0]) ;

	glUseProgram(0);

	glGenVertexArrays(1, &sphere_vao);
	glBindVertexArray(sphere_vao);

	glGenBuffers(1, &sphere_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
	glBufferData(GL_ARRAY_BUFFER, nFloats * sizeof(float) , &vertexData[0], GL_DYNAMIC_COPY);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//color	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	//Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, sphere_vbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0, sphere_vbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &sphere_centers_buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, sphere_centers_buffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sphere_centers.size() * sizeof(float), &sphere_centers[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sphere_centers_buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}

void Rectangle::init_lines() {
	
	shader.setUpShader("line.vs", "line.frag", "");
	line_program = shader.programNonComputeShader;

	glGenVertexArrays(1, &line_vao);
	glBindVertexArray(line_vao);

	glGenBuffers(1, &line_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, line_vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	//Capacity for milion vertices
	glBufferData(GL_ARRAY_BUFFER, 1024 * 1024 * 3 * sizeof(float), NULL, GL_DYNAMIC_COPY);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, line_vbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, line_vbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glBindVertexArray(0);
	
}

//Returns the new expanded buffer
GLuint Rectangle::expandBuffer(GLuint buffer, GLint numOfBytes) {

	void *p1, *p2;

	GLuint newBuffer;
	glGenBuffers(1, &newBuffer);
	GLint size;
	glBindBuffer(GL_COPY_READ_BUFFER, buffer);
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

	glBindBuffer(GL_COPY_WRITE_BUFFER, newBuffer);

	glBufferData(GL_COPY_WRITE_BUFFER, size + numOfBytes, NULL, GL_DYNAMIC_COPY);

	if(size > 0)
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,0 ,0 ,size);

	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
	
	glDeleteBuffers(1, &buffer);

	return newBuffer;
}