#pragma once
#include<utility>
#include<string>
using namespace std;

class Configuration {
public:

	string vector_field_x = "2*pos.y";
	string vector_field_y = "pos.z";
	string vector_field_z = "0";

	int	PARTICLE_GROUP_SIZE = 128;
	int PARTICLE_GROUP_COUNT = 5000;
	
	bool spheres_enabled = false;
	bool particles_enabled = true;

	float particles_start_position_minx = 0;
	float particles_start_position_miny = 0;
	float particles_start_position_minz = 0;

	float particles_start_position_maxx = 0.1;
	float particles_start_position_maxy = 0.1;
	float particles_start_position_maxz = 0.1;
	
	int spheres_count = 1;
	float spheres_radius = 3;
	int sphere_smoothness = 2;

	float spheres_color_red = 0.6;
	float spheres_color_green = 0.6;
	float spheres_color_blue = 0.6;

	float spheres_start_position_minx = 0;
	float spheres_start_position_miny = 0;
	float spheres_start_position_minz = 0;

	float spheres_start_position_maxx = 0.1;
	float spheres_start_position_maxy = 0.1;
	float spheres_start_position_maxz = 0.1;

	std::pair<string, string> getKeyValueFromString(string line);

	bool load_configuration(char *configFilename);
	int getParticleCount() {
		return PARTICLE_GROUP_COUNT * PARTICLE_GROUP_SIZE;
	}

	void writeVectorFieldToCoreComputeShader();
	void writeVectorFieldToSpheresComputeShader();

};