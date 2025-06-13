// ================================================
// File: renderer.cpp
// Created on: 2025-06-11 18:58:24
// Last modified: 2025-06-12 20:14:52
// Created by: Alwin R Ajeesh
// ================================================

#include "renderer.hpp"
#include "resourceManager.hpp"
#include <GLM/ext/matrix_transform.hpp>

Renderer::Renderer(glm::mat4& projection)
	:m_QuadShader(*ResourceManager::instance()->getShader("quad")), m_SpriteShader(*ResourceManager::instance()->getShader("default"))

{
	initRenderData(projection);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}


void Renderer::initRenderData(glm::mat4& projection)
{
	float vertices[] = 
	{
		//ver			//tex
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f,
		-1.0f,  1.0f,	0.0f, 1.0f,
	};
	
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_QuadShader.bind();
	m_QuadShader.setMatrix4f("projection", projection);
	m_QuadShader.unbind();
	m_SpriteShader.bind();
	m_SpriteShader.setMatrix4f("projection", projection);
	m_SpriteShader.unbind();
}

void Renderer::drawQuad(glm::vec2 f_Position, glm::vec3 f_color, glm::mat4& view, glm::vec2 f_Scale)
{
	glm::mat4 model = glm::mat4(1.0f);
	//trs
	model = glm::translate(model, glm::vec3(f_Position, 0.0f));
	// model = glm::translate(model, glm::vec3(50.0f, 50.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// model = glm::translate(model, glm::vec3(-50.0f, -50.0f, 0.0f));
	model = glm::scale(model, 0.5f * glm::vec3(f_Scale, 0.0f));

	m_QuadShader.bind();
	
	m_QuadShader.setMatrix4f("model", model);
	m_QuadShader.setVector3f("color", f_color);
	m_QuadShader.setMatrix4f("view", view);
	
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::drawSprite(const std::string& textureID, glm::vec2 f_Position, glm::mat4& view, glm::vec2 f_Scale)
{	
	glm::mat4 model = glm::mat4(1.0f);
	//trs
	model = glm::translate(model, glm::vec3(f_Position, 0.0f));
	// model = glm::translate(model, glm::vec3(50.0f, 50.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// model = glm::translate(model, glm::vec3(-50.0f, -50.0f, 0.0f));
	model = glm::scale(model, 0.5f * glm::vec3(f_Scale, 0.0f));

	m_SpriteShader.bind();
	ResourceManager::instance()->useTexture(textureID);
	
	m_SpriteShader.setMatrix4f("model", model);
	m_SpriteShader.setMatrix4f("view", view);
	
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
