// ================================================
// File: texture.cpp
// Created on: 2025-06-07 20:59:18
// Last modified: 2025-06-14 14:28:16
// Created by: Alwin R Ajeesh
// ================================================

#include <stb_image.h>
#include "texture.hpp"
#include "../debug.hpp"

//TODO : maybe make fallback image a globle variable or find a way to encode that into the system? in case it is absent?
//needs work one that......what if it fail?
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
		ERROR_LOG("Failed to create texture from file : " + std::string(filename));
		//fallback image loading
		ERROR_LOG("Loading fallback texture");
		imageData = stbi_load("../src/res/fallback.png", &m_Width, &m_Height, &m_Channels, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	clean();
}

//TODO : take textureunit and bind to that , this may be insuffecent in future ?
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
