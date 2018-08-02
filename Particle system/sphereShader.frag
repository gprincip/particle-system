#version 430 core

out vec4 color;
in vec3 outColor;
in vec3 fragPos;
in vec3 outNormal;

uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{

float ambientStrength = 0.2f;
float specularStrength = 0.5f;
vec3 lightColor = vec3(0.4f, 0.4f, 0.4f);
vec3 ambient = ambientStrength * lightColor;

vec3 normal = normalize(outNormal);

vec3 lightDir = normalize(lightPos - fragPos);
float diff = max(dot(normal, lightDir), 0);
vec3 diffuse = diff * lightColor;

int shininess = 25;
vec3 viewDir = normalize(cameraPos - fragPos);
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
vec3 specular = specularStrength * spec * lightColor;

vec3 result = (ambient + diffuse + specular) * outColor;

color = vec4(result, 1.0f);

}