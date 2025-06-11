// ================================================
// File: shader.hpp
// Created on: 2025-06-01 19:36:58
// Last modified: 2025-06-11 22:21:28
// Created by: Alwin R Ajeesh
// ================================================

#pragma once

#include <GLAD/glad.h>
#include <GLM/ext/matrix_float4x4.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader() { std::cout << "des\n"; }
	void bind();
	void unbind();
	void clean();
	int getId() { return ID; }
	void setBoolean(const std::string& name, bool value) const;
	void setInteger(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVector2f(const std::string& name, float x, float y);
	void setVector3f(const std::string& name, glm::vec3& value);
	void setMatrix4f(const std::string& name, glm::mat4& value);

private:
	unsigned int ID;
	mutable std::unordered_map<std::string, GLint> m_UniformLocations;
	GLint getUniformLocation(const std::string& name) const;
};
