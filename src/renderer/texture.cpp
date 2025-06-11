// ================================================
// File: texture.cpp
// Created on: 2025-06-07 20:59:18
// Last modified: 2025-06-10 20:45:57
// Created by: Alwin R Ajeesh
// ================================================

#include <iostream>
#include <stb_image.h>
#include "texture.hpp"

Texture::Texture(const char* filename)
{

	unsigned char* imageData = stbi_load(filename, &m_Width, &m_Height, &m_Channels, 0);
	
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);
	} else {
		std::cout << "Failed to load texture\n";
		stbi_image_free(imageData);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	clean();
}

void Texture::bind()
{
	// glBindTexture(GL_TEXTURE_2D, 0);
	// glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clean()
{
	glDeleteTextures(1, &m_TextureID);
}
