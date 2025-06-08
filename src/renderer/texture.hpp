// ================================================
// File: texture.hpp
// Created on: 2025-06-06 15:32:47
// Last modified: 2025-06-08 16:20:34
// Created by: Alwin R Ajeesh
// ================================================
#pragma once
#include "GLAD/glad.h"


class Texture
{

public:
	Texture(const char* filename);
	~Texture();

	void bind();
	void unbind();

	void clean();
	

	GLuint getTextureID() { return m_TextureID; }

private:
	GLuint m_TextureID;

	int m_Width, m_Height, m_Channels;

};
