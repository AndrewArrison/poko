// ================================================
// File: player.hpp
// Created on: 2025-06-09 23:14:24
// Last modified: 2025-06-10 16:27:41
// Created by: Alwin R Ajeesh
// ================================================

#include "mesh.hpp"
#include "../renderer/shader.hpp"
#include "../renderer/texture.hpp"
#include <GLM/glm.hpp>


class Player
{

public:

	Player(glm::vec2 pos, Shader& shader, Texture& texture);
	Player(float posX, float posY, Shader& shader, Texture& texture);
	
	void draw( glm::mat4& view, glm::mat4& projection);

private:

	glm::vec2 m_Position;

	Shader& m_Shader;
	Texture& m_Texture;
	Mesh m_Mesh;

};
