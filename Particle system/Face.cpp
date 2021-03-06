#include "Face.h"

std::vector<Face> Face::subdivide(float r, float x, float y, float z, float red, float green, float blue) {

	float t1n[3];
	float t2n[3];
	float t3n[3];

	t1n[0] = t1[0] + (t2[0] - t1[0]) / (float)2.0;
	t1n[1] = t1[1] + (t2[1] - t1[1]) / (float)2.0;
	t1n[2] = t1[2] + (t2[2] - t1[2]) / (float)2.0;

	t2n[0] = t2[0] + (t3[0] - t2[0]) / (float)2.0;
	t2n[1] = t2[1] + (t3[1] - t2[1]) / (float)2.0;
	t2n[2] = t2[2] + (t3[2] - t2[2]) / (float)2.0;

	t3n[0] = t1[0] + (t3[0] - t1[0]) / (float)2.0;
	t3n[1] = t1[1] + (t3[1] - t1[1]) / (float)2.0;
	t3n[2] = t1[2] + (t3[2] - t1[2]) / (float)2.0;

	Face fNew;
	fNew.t1[0] = t1n[0];
	fNew.t1[1] = t1n[1];
	fNew.t1[2] = t1n[2];

	fNew.t2[0] = t2[0];
	fNew.t2[1] = t2[1];
	fNew.t2[2] = t2[2];

	fNew.t3[0] = t2n[0];
	fNew.t3[1] = t2n[1];
	fNew.t3[2] = t2n[2];

	fNew.r = red;
	fNew.g = green;
	fNew.b = blue;
	fNew.normalize(r,x,y,z);

	Face fNew2;
	fNew2.t1[0] = t3n[0];
	fNew2.t1[1] = t3n[1];
	fNew2.t1[2] = t3n[2];

	fNew2.t2[0] = t2n[0];
	fNew2.t2[1] = t2n[1];
	fNew2.t2[2] = t2n[2];

	fNew2.t3[0] = t3[0];
	fNew2.t3[1] = t3[1];
	fNew2.t3[2] = t3[2];

	fNew2.r = red;
	fNew2.g = green;
	fNew2.b = blue;
	fNew2.normalize(r, x, y, z);

	Face fNew3;
	fNew3.t1[0] = t1n[0];
	fNew3.t1[1] = t1n[1];
	fNew3.t1[2] = t1n[2];

	fNew3.t2[0] = t2n[0];
	fNew3.t2[1] = t2n[1];
	fNew3.t2[2] = t2n[2];

	fNew3.t3[0] = t3n[0];
	fNew3.t3[1] = t3n[1];
	fNew3.t3[2] = t3n[2];

	fNew3.r = red;
	fNew3.g = green;
	fNew3.b = blue;
	fNew3.normalize(r, x, y, z);

	t2[0] = t1n[0];
	t2[1] = t1n[1];
	t2[2] = t1n[2];

	t3[0] = t3n[0];
	t3[1] = t3n[1];
	t3[2] = t3n[2];

	normalize(r, x, y, z);

	//Returns 4 new faces made from the original (this) face
	std::vector<Face> newFaces;
	newFaces.push_back(fNew);
	newFaces.push_back(fNew2);
	newFaces.push_back(fNew3);
	newFaces.push_back(*this);

	return newFaces;
}

void Face::normalize(float r, float x, float y, float z) {

	//Translate line (c,t) to (0,0,0) and normalize it
	//c - center of the sphere
	//t - triangle vertices

	float t1x = t1[0] - x;
	float t1y = t1[1] - y;
	float t1z = t1[2] - z;

	float t2x = t2[0] - x;
	float t2y = t2[1] - y;
	float t2z = t2[2] - z;

	float t3x = t3[0] - x;
	float t3y = t3[1] - y;
	float t3z = t3[2] - z;

	//Calculate norms

	float t1Norm = sqrt(
		t1x * t1x + t1y * t1y + t1z * t1z
	);
	float t2Norm = sqrt(
		t2x * t2x + t2y * t2y + t2z * t2z
	);

	float t3Norm = sqrt(
		t3x * t3x + t3y * t3y + t3z * t3z
	);

	//Normalize

	t1x /= t1Norm;
	t1y /= t1Norm;
	t1z /= t1Norm;

	t2x /= t2Norm;
	t2y /= t2Norm;
	t2z /= t2Norm;

	t3x /= t3Norm;
	t3y /= t3Norm;
	t3z /= t3Norm;

	//Set radius

	t1x *= r;
	t1y *= r;
	t1z *= r;

	t2x *= r;
	t2y *= r;
	t2z *= r;

	t3x *= r;
	t3y *= r;
	t3z *= r;

	//Return normalized lines back to the center of the sphere

	t1[0] = t1x + x;
	t1[1] = t1y + y;
	t1[2] = t1z + z;

	t2[0] = t2x + x;
	t2[1] = t2y + y;
	t2[2] = t2z + z;

	t3[0] = t3x + x;
	t3[1] = t3y + y;
	t3[2] = t3z + z;

}
