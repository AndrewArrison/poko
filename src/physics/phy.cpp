// ================================================
// File: phy.cpp
// Created on: 2025-06-17 13:08:02
// Last modified: 2025-06-18 14:34:12
// Created by: Alwin R Ajeesh
// ================================================

#include "phy.hpp"
#include "../debug.hpp"


bool Physics::isRectColliding(int x1, int x2, int y1, int y2, int h1, int h2, int w1, int w2)
{
	// if (
	// 	x1 < x2 + w2 &&
	// 	x1 + w1 > x2 &&
	// 	y1 < y2 + h2 &&
	// 	y1 + h1 > y2
	// ) {
	// 	// DEBUG_LOG("IS RECT COLLIDE");
	// 	return true;
	// }
	// DEBUG_LOG("IS RECT");
	return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);

}
//
//z = h
//w = w
//x,y,z,w
bool Physics::isRectColliding(glm::vec4& rect1, glm::vec4& rect2)
{
	// if (
	// 	rect1.x < rect2.x + rect2.w &&
	// 	rect1.x + rect1.w > rect2.x &&
	// 	rect1.y < rect2.y + rect2.z &&
	// 	rect1.y + rect1.z > rect2.y
	// ) {
	// 	// DEBUG_LOG("IS RECT COLLIDE");
	// }
	return (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.z && rect1.y + rect1.z > rect2.y);
}
