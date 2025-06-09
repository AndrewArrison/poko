// ================================================
// File: resourceManager.hpp
// Created on: 2025-06-08 14:56:18
// Last modified: 2025-06-08 19:17:39
// Created by: Alwin R Ajeesh
// ================================================

#include <string>
#include <GLAD/glad.h>
#include "shader.hpp"
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
	
	//Texture
	bool loadTexture(const char* filename, const std::string& textureID);
	Texture* getTexture(const std::string& textureID);
	void useTexture(const std::string& textureID);
	void deleteTexture(const std::string& textureID);

	//Shader
	bool loadShader(const std::string& filename, const std::string& shaderID);
	Shader* getShader(const std::string& shaderID);
	void useShader(const std::string& shaderID);
	void deleteShader(const std::string& shaderID);
	

private:
	
	std::unordered_map<std::string, Texture*> m_TextureResource;
	std::unordered_map<std::string, Shader*> m_ShaderResource;

	static ResourceManager* s_pInstance;
	ResourceManager() { }


};
