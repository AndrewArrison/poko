// ================================================
// File: resourceManager.cpp
// Created on: 2025-06-08 15:01:45
// Last modified: 2025-06-09 15:13:46
// Created by: Alwin R Ajeesh
// ================================================
#include "resourceManager.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "../Timer.hpp"
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
	Timer timer;
	m_TextureResource[textureID]->bind();
}

void ResourceManager::deleteTexture(const std::string& textureID)
{
	m_TextureResource[textureID]->clean();
	std::cout << "Deleted Texture\n";
	delete m_TextureResource[textureID];
	if (!glIsTexture(m_TextureResource[textureID]->getTextureID())) {
		std::cout << "Really deleted\n";
	} else {
		std::cout << "mm not really\n";
	}
	m_TextureResource.erase(textureID);
}

//Shader
bool ResourceManager::loadShader(const std::string& filename, const std::string& shaderID)
{
	Timer timer;
	if (m_ShaderResource.find(shaderID) == m_ShaderResource.end())
	{
		Shader* tempShader = new Shader((filename + ".vs").c_str(), (filename + ".fs").c_str());
		m_ShaderResource[shaderID] = tempShader;
		std::cout << "Shader didnt exist, created and stored\n";
		return true;
	} 
	else 
	{
		std::cout << "Shader exisites\n";
		return true;
	}
}

Shader* ResourceManager::getShader(const std::string& shaderID)
{
	return m_ShaderResource[shaderID];
}

void ResourceManager::useShader(const std::string& shaderID)
{
	m_ShaderResource[shaderID]->bind();
}

void ResourceManager::deleteShader(const std::string& shaderID)
{
	m_ShaderResource[shaderID]->clean();
	std::cout << "Deleted Shader\n";
	delete m_ShaderResource[shaderID];
	if (!glIsShader(m_ShaderResource[shaderID]->getId())) {
		std::cout << "Shader Deleted Really\n";
	} else {
		std::cout << "mm not really s\n";
	}
	m_ShaderResource.erase(shaderID);
}
