// ================================================
// File: game.cpp
// Created on: 2025-06-18 12:24:29
// Last modified: 2025-06-18 14:34:39
// Created by: Alwin R Ajeesh
// ================================================

#include "game.hpp"
#include <GLFW/glfw3.h>
#include <GLM/ext/matrix_clip_space.hpp>
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
}

glm::vec4 r1 = {200, 200, 50, 50};
glm::vec4 r2 = {490, 200, 50, 50};

void Game::ProcessInput(float dt)
{
	if (State == GAME_ACTIVE) {
		if (Keys[GLFW_KEY_A]) {
			r1.x -= 500*dt;
		}
		if (Keys[GLFW_KEY_D]) {
			r1.x += 500*dt;
		}
	}

}

void Game::Update(float dt)
{
	if (Physics::isRectColliding(r1, r2)) {
		WARN_LOG("COLLIDE");
	}
}

void Game::Render()
{
	glm::mat4 view = camera.GetViewMatrix();

	renderer->drawQuad(glm::vec2(r1.x, r1.y), glm::vec3(0.3f, 0.432f, 0.1f), view, glm::vec2(50.0f, 50.0f));
	renderer->drawSprite("TestTexture", glm::vec2(r2.x, r2.y), view, glm::vec2(50.0f, 50.0f));
	Physics::isRectColliding(r1, r2);

}
