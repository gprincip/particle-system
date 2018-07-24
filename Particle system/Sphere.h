#pragma once
#include "Face.h"
#include "Mesh_global.h"
#include "Shader.h"

class Sphere {

public:
	//center
	float x, y, z;

	Face f1;
	Face f2;
	Face f3;
	Face f4;
	Face f5;
	Face f6;
	Face f7;
	Face f8;

	Sphere();

	void subdivide(int iterations, float x, float y, float z);

};