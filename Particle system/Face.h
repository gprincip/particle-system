#pragma once
#include"GL\glm\common.hpp"
#include"GL\glm\gtc\matrix_transform.hpp"
#include<vector>

class Face {
public:

	glm::vec3 t1;
	glm::vec3 t2;
	glm::vec3 t3;

	glm::vec3 normal;

	float r;
	float g; 
	float b;

	std::vector<Face> subdivide(float r, float x, float y, float z, float red, float green, float blue);

	void normalize(float r, float x, float y, float z);

};