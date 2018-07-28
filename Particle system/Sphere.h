#pragma once
#include "Face.h"
#include "Shader.h"

class Sphere {

public:

	float x, y, z, r;

	std::vector<Face> faces;

	Sphere();

	void constructSphere(int r, float cx, float cy, float cz);

	int getNumberOfFloats() {
		return (faces.size() * 6 * 3);
	}

	void subdivide(int iterations);

	float *getFloats();

};