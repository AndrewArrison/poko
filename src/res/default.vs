#version 430 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in vec2 TextCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(Pos, 1.0, 1.0);
	TexCoord = TextCoord;
}
