#include "Shader.h"

bool Shader::CreateShader(unsigned int &shaderInstance, unsigned int shaderType, const GLchar* shaderSource) {
	
	shaderInstance = glCreateShader(shaderType);

	// 1 stands for one string in vertexShaderSource
	glShaderSource(shaderInstance, 1, &shaderSource, NULL);
	glCompileShader(shaderInstance);

	glGetShaderiv(shaderInstance, GL_COMPILE_STATUS, &success);
		
	if (!success) {
		glGetShaderInfoLog(shaderInstance, 512, NULL, infoLog);
		// std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return success;
}
