// ================================================
// File: game.hpp
// Created on: 2025-06-18 12:18:06
// Last modified: 2025-06-19 15:05:27
// Created by: Alwin R Ajeesh
// ================================================

#pragma once

#include "core/camera.hpp"
#include "core/renderer.hpp"
#include "entities/player.hpp"
#include "entities/ball.hpp"
// #include <GLM/ext/matrix_float4x4.hpp>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	GameState State;
	unsigned int Width, Height;
	bool Keys[1024];

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

private:
	Camera camera;
	Renderer* renderer;
	Player* player;
	glm::vec2 r1 = { Width - 20 , 55};
	Ball* ball;
};



