#version 430 core

layout (location = 0) in vec4 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float intensity;

void main(void)
{
  intensity = Position.w;
  gl_Position = projection * view * model * vec4(Position.xyz, 1.0f);
}