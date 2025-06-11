#version 430 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool test;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 1.0, 1.0);
	TexCoord = aTexCoord;
}
