#include "Sphere.h"

Sphere::Sphere() {}

void Sphere::constructSphere(int r, float cx, float cy, float cz) {

	x = cx;
	y = cy;
	z = cz;
	this->r = r;

	Face f1;

	f1.t1[0] = cx + 1.0f;
	f1.t1[1] = cy;
	f1.t1[2] = cz;

	f1.t2[0] = cx;
	f1.t2[1] = cy;
	f1.t2[2] = cz - 1.0f;

	f1.t3[0] = cx;
	f1.t3[1] = cy + 1.0f;
	f1.t3[2] = cz;

	f1.r = rand() / (float)RAND_MAX;
	f1.g = rand() / (float)RAND_MAX;
	f1.b = rand() / (float)RAND_MAX;

	Face f2;

	f2.t1[0] = cx;
	f2.t1[1] = cy;
	f2.t1[2] = cz - 1.0f;

	f2.t2[0] = cx;
	f2.t2[1] = cy + 1.0f;
	f2.t2[2] = cz;

	f2.t3[0] = cx - 1.0f;
	f2.t3[1] = cy;
	f2.t3[2] = cz;

	f2.r = rand() / (float)RAND_MAX;
	f2.g = rand() / (float)RAND_MAX;
	f2.b = rand() / (float)RAND_MAX;

	Face f3;

	f3.t1[0] = cx;
	f3.t1[1] = cy;
	f3.t1[2] = cz - 1.0f;

	f3.t2[0] = cx + 1.0f;
	f3.t2[1] = cy;
	f3.t2[2] = cz;

	f3.t3[0] = cx;
	f3.t3[1] = cy - 1.0f;
	f3.t3[2] = cz;

	f3.r = rand() / (float)RAND_MAX;
	f3.g = rand() / (float)RAND_MAX;
	f3.b = rand() / (float)RAND_MAX;

	Face f4;

	f4.t1[0] = cx;
	f4.t1[1] = cy;
	f4.t1[2] = cz - 1.0f;

	f4.t2[0] = cx;
	f4.t2[1] = cy - 1.0f;
	f4.t2[2] = cz;

	f4.t3[0] = cx - 1.0f;
	f4.t3[1] = cy;
	f4.t3[2] = cz;

	f4.r = rand() / (float)RAND_MAX;
	f4.g = rand() / (float)RAND_MAX;
	f4.b = rand() / (float)RAND_MAX;

	Face f5;

	f5.t1[0] = cx + 1.0f;
	f5.t1[1] = cy;
	f5.t1[2] = cz;

	f5.t2[0] = cx;
	f5.t2[1] = cy - 1.0f;
	f5.t2[2] = cz;

	f5.t3[0] = cx;
	f5.t3[1] = cy;
	f5.t3[2] = cz + 1.0f;

	f5.r = rand() / (float)RAND_MAX;
	f5.g = rand() / (float)RAND_MAX;
	f5.b = rand() / (float)RAND_MAX;

	Face f6;

	f6.t1[0] = cx;
	f6.t1[1] = cy - 1.0f;
	f6.t1[2] = cz;

	f6.t2[0] = cx;
	f6.t2[1] = cy;
	f6.t2[2] = cz + 1.0f;

	f6.t3[0] = cx - 1.0f;
	f6.t3[1] = cy;
	f6.t3[2] = cz;

	f6.r = rand() / (float)RAND_MAX;
	f6.g = rand() / (float)RAND_MAX;
	f6.b = rand() / (float)RAND_MAX;

	Face f7;

	f7.t1[0] = cx + 1.0f;
	f7.t1[1] = cy;
	f7.t1[2] = cz;

	f7.t2[0] = cx;
	f7.t2[1] = cy;
	f7.t2[2] = cz + 1.0f;

	f7.t3[0] = cx;
	f7.t3[1] = cy + 1.0f;
	f7.t3[2] = cz;

	f7.r = rand() / (float)RAND_MAX;
	f7.g = rand() / (float)RAND_MAX;
	f7.b = rand() / (float)RAND_MAX;

	Face f8;

	f8.t1[0] = cx;
	f8.t1[1] = cy;
	f8.t1[2] = cz + 1.0f;

	f8.t2[0] = cx;
	f8.t2[1] = cy + 1.0f;
	f8.t2[2] = cz;

	f8.t3[0] = cx - 1.0f;
	f8.t3[1] = cy;
	f8.t3[2] = cz;

	f8.r = rand() / (float)RAND_MAX;
	f8.g = rand() / (float)RAND_MAX;
	f8.b = rand() / (float)RAND_MAX;

	faces.push_back(f1);
	faces.push_back(f2);
	faces.push_back(f3);
	faces.push_back(f4);
	faces.push_back(f5);
	faces.push_back(f6);
	faces.push_back(f7);
	faces.push_back(f8);

}

void Sphere::subdivide(int iterations) {

	while (iterations > 0) {

		std::vector<Face> old = faces;
		faces.clear();

		for (int i = 0; i < old.size(); i++) {

			std::vector<Face> newFaces = old[i].subdivide(r,x,y,z);

			for (Face f : newFaces) {

				faces.push_back(f);

			}

		}

		iterations--;

	}
}

float * Sphere::getFloats() {

	float *arr = new float[6 * 3 * faces.size()];

	int ind = 0;

	for (int i = 0; i < faces.size(); i++) {

		arr[ind++] = faces[i].t1[0];
		arr[ind++] = faces[i].t1[1];
		arr[ind++] = faces[i].t1[2];

		arr[ind++] = faces[i].r;
		arr[ind++] = faces[i].g;
		arr[ind++] = faces[i].b;

		arr[ind++] = faces[i].t2[0];
		arr[ind++] = faces[i].t2[1];
		arr[ind++] = faces[i].t2[2];

		arr[ind++] = faces[i].r;
		arr[ind++] = faces[i].g;
		arr[ind++] = faces[i].b;

		arr[ind++] = faces[i].t3[0];
		arr[ind++] = faces[i].t3[1];
		arr[ind++] = faces[i].t3[2];

		arr[ind++] = faces[i].r;
		arr[ind++] = faces[i].g;
		arr[ind++] = faces[i].b;
	}

	return arr;
}
