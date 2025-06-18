// ================================================
// File: inputManager.hpp
// Created on: 2025-06-18 11:49:29
// Last modified: 2025-06-18 11:54:17
// Created by: Alwin R Ajeesh
// ================================================

#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

enum class KeyState
{
	None,
	Pressed,
	Held,
	Released
};

class InputManager
{
	
public:
	void init(GLFWwindow* window);
	void update();

	bool pressed(int key);
	bool held(int key);
	bool released(int key);

private:
	GLFWwindow* m_window = nullptr;
	std::unordered_map<int, KeyState> keys;
};
