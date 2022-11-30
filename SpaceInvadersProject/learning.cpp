
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
//#include<SOIL2/SOIL2.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<stb/stb_image.h>

#include "shaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"

int screenWidth = 800, screenHeight = 600;

//keys and their associated functions
void inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//move left
		std::cout << "moving left" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//move right
		std::cout << "moving right" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		//shoot
		std::cout << "shoot" << std::endl;
	}
}

int main()
{
	glfwInit();

	//Tells GLFW what version of OpenGl we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tells GLFW we are using CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//floats that GL uses to determine points
	// //every 3 floats represent a coordinate
	//coordinates can be anything between -1 and 1
	GLfloat vertices[] =
	{	//position					//color						//texture coordinates
		-0.5f, 0.5f, 0.0f,			0.2f,0.5f,0.82f,			0.0f, 1.0f,	//top left
		-0.5f, -0.5f, 0.0f,			0.25f,0.6f,0.9f,			0.0f, 0.0f,	//bottom left
		0.5f, 0.5f, 0.0f,			0.2f,0.5f,0.82f,			1.0f, 1.0f,	//top right
		0.5f, -0.5f,0.0f,			0.25f,0.6f,0.9f,			1.0f, 0.0f	//bottom right
	};

	GLuint indices[] =
	{
		1,2,3,
		0,1,2
	};

	//creates window object in 800x600 pixels
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "SpaceInvaders", NULL, NULL);
	//Error if window does not open
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//opens window
	glfwMakeContextCurrent(window);

	//load glad
	gladLoadGL();

	//specifies the viewport of OpenGL
	//top left corner coordinates (0,0) to bottom right coordinates (800,600)
	glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("core.vs","core.frag");

	//enable textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//virtual buffer object
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(ourShader.ID, "scale");

	//Textures
	Texture zoroark("zoro.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	zoroark.texUnit(ourShader, "tex0",0);

	//Main while loop
	//closes when window is closed
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//tells opengl which shader to use
		//glUseProgram(shaderProgram);
		ourShader.Activate();

		//input reading
		inputs(window);

		glUniform1f(uniID, 0.0f);
		zoroark.Bind();

		/*
		//transformation (aka moving)
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform,(GLfloat)glfwGetTime() *-5.0f,  glm::vec3(0.0f, 0.0f, 1.0f));

		GLint transformLocation = glGetUniformLocation(ourShader.ID, "transform");

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
		*/

		VAO1.Bind();

		//draws triangle 
		//glDrawArrays(GL_TRIANGLES, 0, 3); //replaced with next line
		//data, number of indicies, datatype, index
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		//updates GLFW
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ourShader.Delete();
	zoroark.Delete();

	//closes window when program ends
	glfwDestroyWindow(window);
	//closes GLFW
	glfwTerminate();
	return 0;
}