#pragma once

#include "Face.h"
#include <vector>
using namespace std;

class Mesh {

public:
	vector<Face> faces;

	float *getVertices() {

		//6(r,g,b,x,y,z) * 3(temena trougla)
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

};