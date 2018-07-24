#version 430 core

out vec4 color;
in vec3 outColor;

void main()
{
color = vec4(outColor.xyz, 1.0f);
};