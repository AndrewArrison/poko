#version 430 core

out vec4 FragColor;

in vec3 m_color;

void main()
{
	//FragColor = vec4(0.3f, 1.0f, 0.8f, 1.0f);
	FragColor = vec4(m_color, 1.0f);
}
