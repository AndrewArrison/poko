// ================================================
// File: mesh.hpp
// Created on: 2025-06-09 23:57:08
// Last modified: 2025-06-10 00:10:35
// Created by: Alwin R Ajeesh
// ================================================
#pragma once

class Mesh
{

public:
	Mesh();
	~Mesh();

	void bind() const;
	void unbind() const;
	void draw() const;


private:
	unsigned int m_VAO, m_VBO;

};
