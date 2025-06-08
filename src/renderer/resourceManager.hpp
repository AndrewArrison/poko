// ================================================
// File: resourceManager.hpp
// Created on: 2025-06-08 14:56:18
// Last modified: 2025-06-08 16:17:53
// Created by: Alwin R Ajeesh
// ================================================

#include <string>
#include <GLAD/glad.h>
#include "texture.hpp"
#include <unordered_map>

class ResourceManager
{

public:
	
	static ResourceManager* instance()
	{
		if (s_pInstance == nullptr) {
			s_pInstance = new ResourceManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool loadTexture(const char* filename, const std::string& textureID);
	Texture* getTexture(const std::string& textureID);
	void useTexture(const std::string& textureID);
	void deleteTexture(const std::string& textureID);

private:
	
	std::unordered_map<std::string, Texture*> m_TextureResource;

	static ResourceManager* s_pInstance;
	ResourceManager() { }


};
