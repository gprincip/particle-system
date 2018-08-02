#include "Sphere.h"

Sphere::Sphere() {}

void Sphere::constructSphere(float r, float cx, float cy, float cz, float red, float green, float blue) {

	x = cx;
	y = cy;
	z = cz;
	this->r = r;
	this->red = red;
	this->green = green;
	this->blue = blue;

	Face f1;
	f1.normalize(r, x, y, z);

	f1.t1[0] = cx + 1.0f;
	f1.t1[1] = cy;
	f1.t1[2] = cz;

	f1.t2[0] = cx;
	f1.t2[1] = cy;
	f1.t2[2] = cz - 1.0f;

	f1.t3[0] = cx;
	f1.t3[1] = cy + 1.0f;
	f1.t3[2] = cz;

	f1.r = red;
	f1.g = green;
	f1.b = blue;

	Face f2;
	f2.normalize(r, x, y, z);

	f2.t1[0] = cx;
	f2.t1[1] = cy;
	f2.t1[2] = cz - 1.0f;

	f2.t2[0] = cx;
	f2.t2[1] = cy + 1.0f;
	f2.t2[2] = cz;

	f2.t3[0] = cx - 1.0f;
	f2.t3[1] = cy;
	f2.t3[2] = cz;

	f2.r = red;
	f2.g = green;
	f2.b = blue;

	Face f3;
	f3.normalize(r, x, y, z);

	f3.t1[0] = cx;
	f3.t1[1] = cy;
	f3.t1[2] = cz - 1.0f;

	f3.t2[0] = cx + 1.0f;
	f3.t2[1] = cy;
	f3.t2[2] = cz;

	f3.t3[0] = cx;
	f3.t3[1] = cy - 1.0f;
	f3.t3[2] = cz;

	f3.r = red;
	f3.g = green;
	f3.b = blue;

	Face f4;
	f4.normalize(r, x, y, z);

	f4.t1[0] = cx;
	f4.t1[1] = cy;
	f4.t1[2] = cz - 1.0f;

	f4.t2[0] = cx;
	f4.t2[1] = cy - 1.0f;
	f4.t2[2] = cz;

	f4.t3[0] = cx - 1.0f;
	f4.t3[1] = cy;
	f4.t3[2] = cz;

	f4.r = red;
	f4.g = green;
	f4.b = blue;

	Face f5;
	f5.normalize(r, x, y, z);

	f5.t1[0] = cx + 1.0f;
	f5.t1[1] = cy;
	f5.t1[2] = cz;

	f5.t2[0] = cx;
	f5.t2[1] = cy - 1.0f;
	f5.t2[2] = cz;

	f5.t3[0] = cx;
	f5.t3[1] = cy;
	f5.t3[2] = cz + 1.0f;

	f5.r = red;
	f5.g = green;
	f5.b = blue;

	Face f6;
	f6.normalize(r, x, y, z);

	f6.t1[0] = cx;
	f6.t1[1] = cy - 1.0f;
	f6.t1[2] = cz;

	f6.t2[0] = cx;
	f6.t2[1] = cy;
	f6.t2[2] = cz + 1.0f;

	f6.t3[0] = cx - 1.0f;
	f6.t3[1] = cy;
	f6.t3[2] = cz;

	f6.r = red;
	f6.g = green;
	f6.b = blue;

	Face f7;
	f7.normalize(r, x, y, z);

	f7.t1[0] = cx + 1.0f;
	f7.t1[1] = cy;
	f7.t1[2] = cz;

	f7.t2[0] = cx;
	f7.t2[1] = cy;
	f7.t2[2] = cz + 1.0f;

	f7.t3[0] = cx;
	f7.t3[1] = cy + 1.0f;
	f7.t3[2] = cz;

	f7.r = red;
	f7.g = green;
	f7.b = blue;

	Face f8;
	f8.normalize(r, x, y, z);

	f8.t1[0] = cx;
	f8.t1[1] = cy;
	f8.t1[2] = cz + 1.0f;

	f8.t2[0] = cx;
	f8.t2[1] = cy + 1.0f;
	f8.t2[2] = cz;

	f8.t3[0] = cx - 1.0f;
	f8.t3[1] = cy;
	f8.t3[2] = cz;

	f8.r = red;
	f8.g = green;
	f8.b = blue;

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

			std::vector<Face> newFaces = old[i].subdivide(r,x,y,z, red, green, blue);

			for (Face f : newFaces) {

				faces.push_back(f);

			}

		}

		iterations--;

	}
}

float * Sphere::getFloats() {

	float *arr = new float[9 * 3 * faces.size()];

	int ind = 0;

	for (int i = 0; i < faces.size(); i++) {

		//Coordinates
		arr[ind++] = faces[i].t1[0];
		arr[ind++] = faces[i].t1[1];
		arr[ind++] = faces[i].t1[2];

		//Color
		arr[ind++] = faces[i].r;
		arr[ind++] = faces[i].g;
		arr[ind++] = faces[i].b;

		//Normals (not normalized!)
		arr[ind++] = faces[i].t1[0] - x;
		arr[ind++] = faces[i].t1[1] - y;
		arr[ind++] = faces[i].t1[2] - z;

		arr[ind++] = faces[i].t2[0];
		arr[ind++] = faces[i].t2[1];
		arr[ind++] = faces[i].t2[2];

		arr[ind++] = faces[i].r;
		arr[ind++] = faces[i].g;
		arr[ind++] = faces[i].b;

		arr[ind++] = faces[i].t2[0] - x;
		arr[ind++] = faces[i].t2[1] - y;
		arr[ind++] = faces[i].t2[2] - z;

		arr[ind++] = faces[i].t3[0];
		arr[ind++] = faces[i].t3[1];
		arr[ind++] = faces[i].t3[2];

		arr[ind++] = faces[i].r;
		arr[ind++] = faces[i].g;
		arr[ind++] = faces[i].b;

		arr[ind++] = faces[i].t3[0] - x;
		arr[ind++] = faces[i].t3[1] - y;
		arr[ind++] = faces[i].t3[2] - z;

	}

	return arr;
}
