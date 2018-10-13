#include"Configuration.h"

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

bool Configuration::load_configuration(char *configFilename) {

	string line;

	ifstream file(configFilename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line.length() > 2 && line[0] != '#') {

				std::pair<string, string> pair = getKeyValueFromString(line);
				
				if (pair.first.length() < 1 || pair.second.length() < 1) {

					cout << "Error occured while reading configuration for entry key=" << pair.first <<
						", value=" << pair.second << ". Maybe the key or value is empty, or the property is unknown." << endl;

				}
				else if (pair.first == "config.particle_group_count") {

					PARTICLE_GROUP_COUNT = stoi(pair.second);

				}
				else if (pair.first == "config.particle_group_size") {

					PARTICLE_GROUP_SIZE = stoi(pair.second);

				}
				else if (pair.first == "config.particles.enabled") {

					particles_enabled = (pair.second == "true" || pair.second == "1") ? true : false;

				}
				else if (pair.first == "config.spheres.enabled") {

					spheres_enabled = (pair.second == "true" || pair.second == "1") ? true : false;

				}
				else if (pair.first == "config.spheres.count") {

					spheres_count = stoi(pair.second);

				}
				else if (pair.first == "config.particles_start_position_minx") {

					particles_start_position_minx = stof(pair.second);

				}
				else if (pair.first == "config.particles_start_position_miny") {

					particles_start_position_miny = stof(pair.second);

				}
				else if (pair.first == "config.particles_start_position_minz") {

					particles_start_position_minz = stof(pair.second);

				}
				else if (pair.first == "config.particles_start_position_maxx") {

					particles_start_position_maxx = stof(pair.second);

				}
				else if (pair.first == "config.particles_start_position_maxy") {

					particles_start_position_maxy = stof(pair.second);

				}
				else if (pair.first == "config.particles_start_position_maxz") {

					particles_start_position_maxz = stof(pair.second);

				}
				else if (pair.first == "config.spheres.radius") {

					spheres_radius = stof(pair.second);

				}
				else if (pair.first == "config.spheres.smoothness") {

					sphere_smoothness = stoi(pair.second);

				}
				else if (pair.first == "config.spheres.color.red") {

					spheres_color_red = stof(pair.second);

				}
				else if (pair.first == "config.spheres.color.green") {

					spheres_color_green = stof(pair.second);

				}
				else if (pair.first == "config.spheres.color.blue") {

					spheres_color_blue = stof(pair.second);

				}
				else if (pair.first == "config.spheres_start_position_minx") {

					spheres_start_position_minx = stof(pair.second);

				}
				else if (pair.first == "config.spheres_start_position_miny") {

					spheres_start_position_miny = stof(pair.second);

				}
				else if (pair.first == "config.spheres_start_position_minz") {

					spheres_start_position_minz = stof(pair.second);

				}
				else if (pair.first == "config.spheres_start_position_maxx") {

					spheres_start_position_maxx = stof(pair.second);

				}
				else if (pair.first == "config.spheres_start_position_maxy") {

					spheres_start_position_maxy = stof(pair.second);

				}
				else if (pair.first == "config.spheres_start_position_maxz") {

					spheres_start_position_maxz = stof(pair.second);

				}
				else {

					cout << "Unknown property: " << pair.first << endl;

				}
				

			}
		}

		file.close();
	}
	else {
		//cannot open file
		return false;
	}
	//everything ok
	return true;
}

std::pair<string,string> Configuration::getKeyValueFromString(string line) {

	string key = "";
	string value = "";
	bool parsingKey = true; //thing currently parsing through

	for (int i = 0; i < line.length(); i++) {

		if (line[i] != '=') {
			if (parsingKey)
				key += line[i];
			else {
				value += line[i];
			}
		}
		else {
			parsingKey = false;
		}

	}

	return std::make_pair(key, value);

}