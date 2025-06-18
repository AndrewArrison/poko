// ================================================
// File: phy.hpp
// Created on: 2025-06-17 13:07:38
// Last modified: 2025-06-18 14:32:01
// Created by: Alwin R Ajeesh
// ================================================

#pragma once

#include <GLM/ext/vector_float4.hpp>
namespace Physics
{

	bool isRectColliding(int x, int x2, int y1, int y2, int h1, int h2, int w1, int w2);
	bool isRectColliding(glm::vec4& rect1, glm::vec4& rect2);
	
}
