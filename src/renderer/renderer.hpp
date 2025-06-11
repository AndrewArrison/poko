// ================================================
// File: renderer.hpp
// Created on: 2025-06-11 18:58:06
// Last modified: 2025-06-11 21:04:10
// Created by: Alwin R Ajeesh
// ================================================

#include "shader.hpp"
#include "texture.hpp"

class Renderer
{

public:
	Renderer(glm::mat4& projection);
	~Renderer();

	void drawQuad(glm::vec2 f_Position, glm::vec2 f_Scale, glm::mat4& view);
	void drawSprite(Texture& p_Texture, glm::vec2 f_Position, glm::vec2 f_Scale);

private:
	void initRenderData(glm::mat4& projection);

	unsigned int m_VBO, m_VAO;

	Shader& m_QuadShader;
	Shader& m_SpriteShader;
	Texture& m_Texture;
};
