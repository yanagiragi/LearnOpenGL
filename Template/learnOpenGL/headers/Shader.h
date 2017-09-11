#pragma once
#ifndef Shader_H
#define Shader_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdarg.h>

#define ERROR_MESSAGE_LOG_SIZE 512

class Shader
{
	public:
		int success;
		char infoLog[ERROR_MESSAGE_LOG_SIZE];
		
		bool CreateShader(unsigned int &shaderInstance, unsigned int shaderType, const GLchar* shaderSource);
		bool CreateProgram(unsigned int &shaderProgramInstance, int n_args, ... );

};

#endif