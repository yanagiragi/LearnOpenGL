#pragma once
#ifndef Shader_H
#define Shader_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Shader
{
	public:
		int success;
		char infoLog[512];
		
		bool CreateShader(unsigned int &shaderInstance, unsigned int shaderType, const GLchar* shaderSource);

};

#endif