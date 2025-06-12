// ================================================
// File: shader.cpp
// Created on: 2025-06-01 19:36:35
// Last modified: 2025-06-12 15:07:36
// Created by: Alwin R Ajeesh
// ================================================

#include "shader.hpp"
#include "../debug.hpp"
#include <GLM/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexSource = vShaderStream.str();
		fragmentSource = fShaderStream.str();
	}
	catch(std::ifstream::failure& e)
	{
		ERROR_LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" + std::string(e.what()));
	}
	const char* vShaderSource = vertexSource.c_str();
	const char* fShaderSource = fragmentSource.c_str();

	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		ERROR_LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog));
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		ERROR_LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog));
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		ERROR_LOG("ERROR::SHADER::PROGRAM::LINK_FAILED\n" + std::string(infoLog));
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	INFO_LOG("Shader created : " + std::string(fragmentPath));
}

void Shader::bind()
{
	glUseProgram(ID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::clean()
{
	glDeleteShader(ID);
}

void Shader::setBoolean(const std::string& name, bool value) const
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setInteger(const std::string& name, int value) const
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setVector2f(const std::string& name, float x, float y) 
{
	glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVector3f(const std::string& name, glm::vec3& value) 
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setMatrix4f(const std::string& name, glm::mat4& value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1,GL_FALSE,glm::value_ptr(value));
}

GLint Shader::getUniformLocation(const std::string& name) const
{
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];

	GLint location = glGetUniformLocation(ID, name.c_str());
	m_UniformLocations[name] = location;
	return location;
}
