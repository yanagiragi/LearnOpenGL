#pragma once
#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>

#include "Shader.h"
#include "Model.h"
#include "Camera.hpp"

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
		 
		unsigned int VAO, VBO, EBO;
		unsigned int vertexShader;
		unsigned int fragmentShader;
		unsigned int shaderProgram;

		char *modelPath = "data/untitled.obj";

		Model model = Model(modelPath);

		Camera mainCamera = Camera();

		// Prepare data
		void Behaviour :: Start()
		{
			Shader generator = Shader();

			generator.CreateShader(vertexShader, GL_VERTEX_SHADER, generator.LoadRawShader("shader/simple.vert").c_str());
			generator.CreateShader(fragmentShader, GL_FRAGMENT_SHADER, generator.LoadRawShader("shader/simple.frag").c_str());

			generator.CreateProgram(shaderProgram, 2, vertexShader, fragmentShader);

			// VAO = vertex attribute object, 1 stands for one buffer
			glGenVertexArrays(1, &VAO);
			// VBO = vertex buffer object
			glGenBuffers(1, &VBO);
			// EBO = element buffer object
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			// vertex buffer type: GL_ARRAY_BUFFER
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			// copy vertex data into buffer's memory
			// GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
			glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex) * model.vertices.size(), &model.vertices[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);

			// 0 is the index of vertex attribute
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (void *)0);
			
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (void *)offsetof(struct vertex, normals));
			
			// clean up
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Behaviour :: Update()
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			// Wireframe Mode
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			// Normal Mode
			// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			// update the uniform of fragment shader
			float time = glfwGetTime();
			float greenValue = (sin(time) / 2.0f) + 0.5f;
			
			int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
			int MVPLocation = glGetUniformLocation(shaderProgram, "MVP");

			glm::mat4 M(1.0f);			
			glm::mat4 V = mainCamera.getV();
			glm::mat4 P = mainCamera.getP();
			glm::mat4 MVP = P * V * M;

			glUseProgram(shaderProgram);			
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &MVP[0][0]);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, 0);

			glDisable(GL_DEPTH_TEST);
		}

		// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
		void Behaviour:: Input(GLFWwindow *window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				mainCamera.eyez += mainCamera.step;
			else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				mainCamera.eyez -= mainCamera.step;
			else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				mainCamera.eyex += mainCamera.step;
			else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				mainCamera.eyex -= mainCamera.step;
			else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
				mainCamera.eyey += mainCamera.step;
			else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
				mainCamera.eyey -= mainCamera.step;

		}

		void Behaviour :: Destroy()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
		}
};

#endif