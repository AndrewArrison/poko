// ================================================
// File: resourceManager.cpp
// Created on: 2025-06-08 15:01:45
// Last modified: 2025-06-14 15:31:07
// Created by: Alwin R Ajeesh
// ================================================
#include "resourceManager.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "../debug.hpp"
#include <string>

//TODO : check if the key name exist and go to fallback name and warn dev, do not overwright IT WILL CAUSE PROBLEMS
//TODO : needs automatic cleaning?
ResourceManager* ResourceManager::s_pInstance = nullptr;

bool ResourceManager::loadTexture(const char* filename, const std::string& textureID)
{
	//Texture did'nt exist and is loaded.
	if (m_TextureResource.find(textureID) == m_TextureResource.end())
	{
		Texture* tempTexture = new Texture(filename);
		m_TextureResource[textureID] = tempTexture;
		INFO_LOG("Loaded Texture : " + textureID);
		return true;
	} 
	else 
	{
		WARN_LOG("Texture Exist : " + textureID);
		ERROR_LOG("RELOADING TEXTURE with same ID!!!");
		return true;
	}
}

//TODO : Return a fallback texture upon invalid or unloaded getTexture calls
Texture* ResourceManager::getTexture(const std::string& textureID)
{
	//Texture do exist and is returned
	if (m_TextureResource.find(textureID) != m_TextureResource.end())
	{
		return m_TextureResource[textureID];
	}
	else
	{
		WARN_LOG("Texture is not loaded : " + textureID);
		return nullptr;
	}
}

void ResourceManager::useTexture(const std::string& textureID)
{
	m_TextureResource[textureID]->bind();
}

void ResourceManager::deleteTexture(const std::string& textureID)
{
	m_TextureResource[textureID]->clean();
	INFO_LOG("Texture Deleted : " + textureID);
	delete m_TextureResource[textureID];
	if (!glIsTexture(m_TextureResource[textureID]->getTextureID())) {
		INFO_LOG("Texture delete GL : " + textureID);
	} else {
		WARN_LOG("Texture not delete GL : " + textureID);
	}
	m_TextureResource.erase(textureID);
}

//Shader
bool ResourceManager::loadShader(const std::string& filename, const std::string& shaderID)
{
	if (m_ShaderResource.find(shaderID) == m_ShaderResource.end())
	{
		Shader* tempShader = new Shader((filename + ".vs").c_str(), (filename + ".fs").c_str());
		m_ShaderResource[shaderID] = tempShader;
		INFO_LOG("Loaded Shader : " + shaderID);
		return true;
	} 
	else 
	{
		WARN_LOG("Shader Exist : " + shaderID);
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
	INFO_LOG("Shader Deleted : " + shaderID);
	delete m_ShaderResource[shaderID];
	if (!glIsShader(m_ShaderResource[shaderID]->getId())) {
		INFO_LOG("Shader Deleted GL : " + shaderID);
	} else {
		WARN_LOG("Texture not delete GL : " + shaderID);
	}
	m_ShaderResource.erase(shaderID);
}
