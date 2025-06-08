// ================================================
// File: resourceManager.cpp
// Created on: 2025-06-08 15:01:45
// Last modified: 2025-06-08 16:23:21
// Created by: Alwin R Ajeesh
// ================================================
#include "resourceManager.hpp"
#include "texture.hpp"
#include <iostream>
#include <string>

ResourceManager* ResourceManager::s_pInstance = nullptr;

bool ResourceManager::loadTexture(const char* filename, const std::string& textureID)
{
	if (m_TextureResource.find(textureID) == m_TextureResource.end())
	{
		Texture* tempTexture = new Texture(filename);
		m_TextureResource[textureID] = tempTexture;
		std::cout << "Texture created and stroed\n";
		return true;
	} 
	else 
	{
		std::cout << "Texture exisites\n";
		return true;
	}
}

Texture* ResourceManager::getTexture(const std::string& textureID)
{
	if (m_TextureResource.find(textureID) != m_TextureResource.end())
	{
		return m_TextureResource[textureID];
	}
	else
	{
		std::cout << "Texture do not Exisit\n";
		return nullptr;
	}
}

void ResourceManager::useTexture(const std::string& textureID)
{
	m_TextureResource[textureID]->bind();
}

void ResourceManager::deleteTexture(const std::string& textureID)
{
	// m_TextureResource[textureID]
	// glDeleteTextures(1, &m_TextureResource[textureID]);
	m_TextureResource[textureID]->clean();
	std::cout << "Deleted Texture\n";
	delete m_TextureResource[textureID];
	m_TextureResource.erase(textureID);
	if (!glIsTexture(m_TextureResource[textureID]->getTextureID())) {
		std::cout << "Really deleted\n";
	} else {
		std::cout << "mm not really\n";
	}
}
