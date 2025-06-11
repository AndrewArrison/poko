// ================================================
// File: player.cpp
// Created on: 2025-06-09 23:14:34
// Last modified: 2025-06-10 21:00:55
// Created by: Alwin R Ajeesh
// ================================================

#include "player.hpp"
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/ext/quaternion_transform.hpp>

Player::Player(glm::vec2 pos, Shader& shader, Texture& texture)
	: m_Position(pos), m_Shader(shader), m_Texture(texture), m_Mesh()
{

}

void Player::draw(glm::mat4& view, glm::mat4& projection)
{

	glm::mat4 model = glm::mat4(1.0f);
	// model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0f, 0.5f, 0.0f));
	model = glm::translate(model, glm::vec3(m_Position, 0.0f));
	model = glm::scale(model, glm::vec3(100.0f, 100.0f, 0.0f));
	m_Shader.bind();
	m_Texture.bind();
	m_Shader.setMatrix4f("model", model);
	m_Shader.setMatrix4f("view", view);
	m_Shader.setMatrix4f("projection", projection);

	m_Mesh.draw();
}
//u = x / image_width and v = y / image_height.
