// ================================================
// File: texture.hpp
// Created on: 2025-06-06 15:32:47
// Last modified: 2025-06-18 14:03:38
// Created by: Alwin R Ajeesh
// ================================================
#pragma once
#include "GLAD/glad.h"
#include <stb_image.h>


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
