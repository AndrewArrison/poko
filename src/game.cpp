// ================================================
// File: game.cpp
// Created on: 2025-06-18 12:24:29
// Last modified: 2025-06-19 15:35:02
// Created by: Alwin R Ajeesh
// ================================================

#include "game.hpp"
#include <GLFW/glfw3.h>
#include <GLM/ext/matrix_clip_space.hpp>
#include <GLM/ext/vector_float2.hpp>
#include "core/resourceManager.hpp"
#include "debug.hpp"
#include "physics/phy.hpp"

Game::Game(unsigned int width, unsigned int height)
	:State(GAME_ACTIVE), Width(width), Height(height), Keys()
{

}

Game::~Game()
{
	delete renderer;
	delete player;
	ResourceManager::instance()->deleteTexture("TestTexture");
	ResourceManager::instance()->deleteShader("default");
	ResourceManager::instance()->deleteShader("quad");
}

void Game::Init()
{
	ResourceManager::instance()->loadTexture("../src/res/wall.jpg", "TestTexture");
	ResourceManager::instance()->loadShader("../src/res/default", "default");
	ResourceManager::instance()->loadShader("../src/res/quad", "quad");
	glm::mat4 projection;
	projection = glm::ortho(0.0f, (float)Width, 0.0f ,(float)Height, -1.0f, 1.0f);
	renderer = new Renderer(projection);
	player = new Player(glm::vec2(25, 60), *ResourceManager::instance()->getShader("quad"), projection);
	ball = new Ball(glm::vec2(player->m_Position.x + 10 + 10, player->m_Position.y), glm::vec2(15, 15));
}

void Game::ProcessInput(float dt)
{
	if (State == GAME_ACTIVE) {
		if (Keys[GLFW_KEY_W]) {
			if (player->m_Position.y >= 45 && player->m_Position.y <= Height - 55)
			{
				player->m_Position.y += 500*dt;
			}
		}
		if (Keys[GLFW_KEY_S]) {
			if (player->m_Position.y <= Height - 45 && player->m_Position.y >= 55)
			{
				player->m_Position.y -= 500*dt;
			}
		}
		if (Keys[GLFW_KEY_UP]) {
			if (r1.y >= 45 && r1.y <= Height - 55)
			{
				r1.y += 500*dt;
			}
		}
		if (Keys[GLFW_KEY_DOWN]) {
			if (r1.y <= Height - 45 && r1.y >= 55)
			{
				r1.y -= 500*dt;
			}
		}
	}

}

//poll move collide resolve update render
void Game::Update(float dt)
{
	ball->move(dt, player->m_Position, r1);
}

void Game::Render()
{
	glm::mat4 view = camera.GetViewMatrix();

	for (int y = 0; y <= 13; y++) {
		renderer->drawQuad(glm::vec2(400, 44.5 * y + 10), glm::vec3(1,1,1), view, glm::vec2(20, 20));
	}

	renderer->drawQuad(glm::vec2(r1.x, r1.y), glm::vec3(1, 1, 1), view, glm::vec2(20, 90.0f));
	player->draw(view);
	renderer->drawQuad(ball->m_Position, glm::vec3(1,1,1), view, ball->m_Size);
	// renderer->drawSprite("TestTexture", glm::vec2(r2.x, r2.y), view, glm::vec2(50.0f, 50.0f));

}
