// ================================================
// File: renderer.hpp
// Created on: 2025-06-11 18:58:06
// Last modified: 2025-06-12 20:15:08
// Created by: Alwin R Ajeesh
// ================================================

#include "shader.hpp"

class Renderer
{

public:
	Renderer(glm::mat4& projection);
	~Renderer();

	void drawQuad(glm::vec2 f_Position, glm::vec3 f_color, glm::mat4& view, glm::vec2 f_Scale = glm::vec2(100.0f, 100.0f));
	void drawSprite(const std::string& textureID, glm::vec2 f_Position, glm::mat4& view, glm::vec2 f_Scale = glm::vec2(100.0f, 100.0f));

private:
	void initRenderData(glm::mat4& projection);

	unsigned int m_VBO, m_VAO;

	Shader& m_QuadShader;
	Shader& m_SpriteShader;
};
