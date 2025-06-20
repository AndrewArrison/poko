// ================================================
// File: ball.hpp
// Created on: 2025-06-19 14:58:42
// Last modified: 2025-06-20 12:29:14
// Created by: Alwin R Ajeesh
// ================================================

#pragma once
#include "../physics/phy.hpp"
#include <GLM/ext/vector_float2.hpp>
class Ball
{

public:
	Ball(glm::vec2 pos, glm::vec2 size);
	glm::vec2 move(float dt, glm::vec2 p1, glm::vec2 p2);
	glm::vec2 m_Position;
	glm::vec2 velo = { 100, 200};
	glm::vec2 m_Size;
	bool isStuck = false;

};

inline Ball::Ball(glm::vec2 pos, glm::vec2 size) : m_Position(pos), m_Size(size)
{

}
inline glm::vec2 Ball::move(float dt, glm::vec2 p1, glm::vec2 p2)
{
	if (!isStuck) {
		m_Position += velo*dt;
		if (m_Position.y + m_Size.y / 2 >= 600.0f)
		{
			velo.y = -velo.y;
			m_Position.y = 600 - m_Size.y /2;
		} 
		if (m_Position.y + m_Size.y / 2 <= 0.0f) {
			velo.y = -velo.y;
			m_Position.y = 0.0 + m_Size.y / 2;
		}

		if (Physics::isRectColliding(glm::vec4(m_Position, m_Size), glm::vec4(p1, 20.0f, 90.0f)))
		{
		
		}

	}
	return m_Position;
}
