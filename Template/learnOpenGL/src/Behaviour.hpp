#pragma once
#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Behaviour 
{
	public:
		const float vertices[12] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		const unsigned int indices[6] = {
			0, 1, 3,
			1, 2, 3
		};

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = ourColor;\n"
			"}\n\0";

		unsigned int VAO, VBO, EBO;
		unsigned int vertexShader;
		unsigned int fragmentShader;
		unsigned int shaderProgram;

		// Prepare data
		void Behaviour :: Start()
		{
			Shader generator = Shader();

			generator.CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
			generator.CreateShader(vertexShader, GL_FRAGMENT_SHADER, fragmentShaderSource);

			generator.CreateProgram(shaderProgram, 2, vertexShader, fragmentShader);

			// VAO = vertex attribute object
			glGenVertexArrays(1, &VAO);
			// VBO = vertex buffer object
			// 1 stands for one buffer
			glGenBuffers(1, &VBO);
			// EBO = element buffer object
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			// vertex buffer type: GL_ARRAY_BUFFER
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			// copy vertex data into buffer's memory
			// GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
			// 0 is the index of vertex attribute
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}

		void Behaviour :: Update()
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Wireframe Mode
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			// Normal Mode
			// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			// update the uniform of fragment shader
			float time = glfwGetTime();
			float greenValue = (sin(time) / 2.0f) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

			glUseProgram(shaderProgram);
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		}

		// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
		void Behaviour:: Input(GLFWwindow *window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}

		void Behaviour :: Destroy()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
		}
};

#endif