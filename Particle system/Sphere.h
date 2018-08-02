#pragma once
#include "Face.h"
#include "Shader.h"

class Sphere {

public:

	float x, y, z, r, red, green, blue;

	std::vector<Face> faces;

	Sphere();

	void constructSphere(float r, float cx, float cy, float cz, float red, float green, float blue);

	int getNumberOfFloats() {
		return (faces.size() * 9 * 3);
	}

	void subdivide(int iterations);

	float *getFloats();

};