#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GL\glew.h"

using namespace std;

class Shader {

public:
	int programNonComputeShader;
	int programComputeShader;

	Shader() {}

	void setUpShader(const char *vertexPath, const char *fragmentPath, const char *computePath) {

		string vertexCode;
		string fragmentCode;
		string computeCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		ifstream cShaderFile;

		//
		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);
		cShaderFile.exceptions(ifstream::badbit);

		try {

			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			cShaderFile.open(computePath);

			std::stringstream vShaderStream, fShaderStream, cShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			cShaderStream << cShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();
			cShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			computeCode = cShaderStream.str();

		}
		catch (ifstream::failure e) {
			cout << "Error reading shader file" << endl;
		}

		const char *vShaderCode = vertexCode.c_str();
		const char *fShaderCode = fragmentCode.c_str();
		const char *cShaderCode = computeCode.c_str();

		int vertex, fragment, compute;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "Error while compiling vertex shader" << infoLog << endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "Error while compiling fragment shader" << infoLog << endl;
		}

		compute = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(compute, 1, &cShaderCode, NULL);
		glCompileShader(compute);

		glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(compute, 512, NULL, infoLog);
			cout << "Error while compiling compute shader" << infoLog << endl;
		}

		programNonComputeShader = glCreateProgram();
		programComputeShader = glCreateProgram();

		if(vertexPath != "") glAttachShader(programNonComputeShader, vertex);
		if (fragmentPath != "") glAttachShader(programNonComputeShader, fragment);
		if (computePath != "") glAttachShader(programComputeShader, compute);
		glLinkProgram(programNonComputeShader);
		if (computePath != "") glLinkProgram(programComputeShader);

		glGetProgramiv(programNonComputeShader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programNonComputeShader, 512, NULL, infoLog);
			cout << "Error while linking non-compute program" << infoLog << endl;
		}

		if (computePath != "") {
			glGetProgramiv(programComputeShader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(programComputeShader, 512, NULL, infoLog);
				cout << "Error while linking compute program" << infoLog << endl;
			}
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (computePath != "") glDeleteShader(compute);
	}

	void use() {
		glUseProgram(programNonComputeShader);
		glUseProgram(programComputeShader);
	}

};