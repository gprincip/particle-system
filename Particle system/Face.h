#pragma once
#include"GL\glm\common.hpp"

class Face {
public:

	glm::vec3 t1;
	glm::vec3 t2;
	glm::vec3 t3;

	float r;
	float g; 
	float b;

	void subdivide(float x, float y, float z);

	void normalize(float x, float y, float z);

};