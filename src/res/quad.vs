#version 430 core

layout (location = 0) in vec2 Pos;

out vec3 m_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

void main()
{
	gl_Position = projection * view * model * vec4(Pos, 0.0, 1.0);
	m_color = color;
}
