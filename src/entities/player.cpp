// ================================================
// File: player.cpp
// Created on: 2025-06-09 23:14:34
// Last modified: 2025-06-19 14:31:00
// Created by: Alwin R Ajeesh
// ================================================

#include "player.hpp"
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/ext/quaternion_transform.hpp>

Player::Player(glm::vec2 pos, Shader& shader, glm::mat4& projection)
	: m_Position(pos), m_Shader(shader), /*m_Texture(texture)**/ m_Mesh()
{
	model = glm::mat4(1.0f);
	m_Shader.bind();
	m_Shader.setMatrix4f("projection", projection);
}


void Player::draw(glm::mat4& view, glm::mat4& projection)
{
	//trs
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_Position, 0.0f));
	//i guess that moving pivot point is not needed? when i try it, it rotates the not supposed way
	// model = glm::translate(model, glm::vec3(50.0f, 50.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// model = glm::translate(model, glm::vec3(-50.0f, -50.0f, 0.0f));
	//
	model = glm::scale(model, 0.5f * glm::vec3(20.0f, 90.0f, 0.0f));
	
	m_Shader.bind();
	
	m_Shader.setMatrix4f("model", model);
	m_Shader.setMatrix4f("view", view);
	m_Shader.setMatrix4f("projection", projection);

	m_Mesh.draw();

}
//u = x / image_width and v = y / image_height.

void Player::draw(glm::mat4& view)
{
	//trs
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_Position, 0.0f));
	//i guess that moving pivot point is not needed? when i try it, it rotates the not supposed way
	// model = glm::translate(model, glm::vec3(50.0f, 50.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// model = glm::translate(model, glm::vec3(-50.0f, -50.0f, 0.0f));
	//
	model = glm::scale(model, 0.5f * glm::vec3(20.0f, 90.0f, 0.0f));
	
	m_Shader.bind();
	
	m_Shader.setMatrix4f("model", model);
	m_Shader.setMatrix4f("view", view);

	m_Mesh.draw();

}

