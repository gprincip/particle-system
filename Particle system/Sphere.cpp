#include "Sphere.h"

Sphere::Sphere() {

	x = 10.0f;
	y = 30.0f;
	z = 0.0f;

	//Forming initial octahedron
	f1.t1[0] = x+1.0f;
	f1.t1[1] = y;
	f1.t1[2] = z;

	f1.t2[0] = x;
	f1.t2[1] = y;
	f1.t2[2] = z-1.0f;

	f1.t3[0] = x;
	f1.t3[1] = y+1.0f;
	f1.t3[2] = z;

	f1.r = rand() / (float)RAND_MAX;
	f1.g = rand() / (float)RAND_MAX;
	f1.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f1);

	f2.t1[0] = x;
	f2.t1[1] = y;
	f2.t1[2] = z-1.0f;

	f2.t2[0] = x;
	f2.t2[1] = y+1.0f;
	f2.t2[2] = z;

	f2.t3[0] = x-1.0f;
	f2.t3[1] = y;
	f2.t3[2] = z;

	f2.r = rand() / (float)RAND_MAX;
	f2.g = rand() / (float)RAND_MAX;
	f2.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f2);

	f3.t1[0] = x;
	f3.t1[1] = y;
	f3.t1[2] = z-1.0f;

	f3.t2[0] = x+1.0f;
	f3.t2[1] = y;
	f3.t2[2] = z;

	f3.t3[0] = x;
	f3.t3[1] = y-1.0f;
	f3.t3[2] = z;

	f3.r = rand() / (float)RAND_MAX;
	f3.g = rand() / (float)RAND_MAX;
	f3.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f3);

	f4.t1[0] = x;
	f4.t1[1] = y;
	f4.t1[2] = z-1.0f;

	f4.t2[0] = x;
	f4.t2[1] = y-1.0f;
	f4.t2[2] = z;

	f4.t3[0] = x-1.0f;
	f4.t3[1] = y;
	f4.t3[2] = z;

	f4.r = rand() / (float)RAND_MAX;
	f4.g = rand() / (float)RAND_MAX;
	f4.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f4);

	f5.t1[0] = x+1.0f;
	f5.t1[1] = y;
	f5.t1[2] = z;

	f5.t2[0] = x;
	f5.t2[1] = y-1.0f;
	f5.t2[2] = z;

	f5.t3[0] = x;
	f5.t3[1] = y;
	f5.t3[2] = z+1.0f;

	f5.r = rand() / (float)RAND_MAX;
	f5.g = rand() / (float)RAND_MAX;
	f5.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f5);

	f6.t1[0] = x;
	f6.t1[1] = y-1.0f;
	f6.t1[2] = z;

	f6.t2[0] = x;
	f6.t2[1] = y;
	f6.t2[2] = z+1.0f;

	f6.t3[0] = x-1.0f;
	f6.t3[1] = y;
	f6.t3[2] = z;

	f6.r = rand() / (float)RAND_MAX;
	f6.g = rand() / (float)RAND_MAX;
	f6.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f6);

	f7.t1[0] = x+1.0f;
	f7.t1[1] = y;
	f7.t1[2] = z;

	f7.t2[0] = x;
	f7.t2[1] = y;
	f7.t2[2] = z+1.0f;

	f7.t3[0] = x;
	f7.t3[1] = y+1.0f;
	f7.t3[2] = z;

	f7.r = rand() / (float)RAND_MAX;
	f7.g = rand() / (float)RAND_MAX;
	f7.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f7);

	f8.t1[0] = x;
	f8.t1[1] = y;
	f8.t1[2] = z+1.0f;

	f8.t2[0] = x;
	f8.t2[1] = y+1.0f;
	f8.t2[2] = z;

	f8.t3[0] = x-1.0f;
	f8.t3[1] = y;
	f8.t3[2] = z;

	f8.r = rand() / (float)RAND_MAX;
	f8.g = rand() / (float)RAND_MAX;
	f8.b = rand() / (float)RAND_MAX;

	mesh.faces.push_back(f8);

}

void Sphere::subdivide(int iterations, float x, float y, float z) {
	while (iterations > 0) {

		Mesh old = mesh;
		mesh.faces.clear();

		for (int i = 0; i < old.faces.size(); i++) {

			old.faces[i].subdivide(x,y,z);

		}

		iterations--;

	}
}