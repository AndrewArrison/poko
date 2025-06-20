// ================================================
// File: player.hpp
// Created on: 2025-06-09 23:14:24
// Last modified: 2025-06-19 14:34:30
// Created by: Alwin R Ajeesh
// ================================================
#pragma once
#include "mesh.hpp"
#include "../core/shader.hpp"
#include "../core/texture.hpp"
#include <GLM/glm.hpp>


class Player
{

public:

	// Player(glm::vec2 pos, Shader& shader, Texture& texture);
	Player(glm::vec2 pos, Shader& shader, glm::mat4& projection);
	Player(float posX, float posY, Shader& shader, Texture& texture);
	
	void draw( glm::mat4& view, glm::mat4& projection);
	void draw( glm::mat4& view);

	glm::vec2 m_Position;

private:

	glm::mat4 model;


	Shader& m_Shader;
	// Texture& m_Texture;
	Mesh m_Mesh;

};
