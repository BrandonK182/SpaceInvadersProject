
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

int screenWidth = 800, screenHeight = 600;

//keys and their associated functions
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		//move left
		std::cout << "moving left" << std::endl;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		//move right
		std::cout << "moving right" << std::endl;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
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
	{	//position										//color						//texture coordinates
		-0.5f, -0.5f * float(sqrt(3))/3, 0.0f,			0.8f,0.3f,0.02f,
		0.5f, -0.5f * float(sqrt(3))/3, 0.0f,			0.8f,0.3f,0.02f,
		0.0f, 0.5f * float(sqrt(3))*2/3, 0.0f,			1.0f,0.6f,0.32f,
		-0.5f/2, 0.5f*float(sqrt(3))/6,0.0f,			0.9f,0.45f,0.17f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6,0.0f,		0.9f,0.45f,0.17f,
		0.0f, -0.5f * float(sqrt(3)) / 3,0.0f,			0.8f,0.3f,0.02f
	};

	GLuint indices[] =
	{
		0,3,5,		//first triangle
		3,4,2,
		5,4,1
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
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(ourShader.ID, "scale");

	/*
	//Textures
	int widthImg, heightImg, numColCh;

	unsigned char* image = stbi_load("zoro.png", &widthImg, &heightImg, 0, 0);
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	*/

	//Main while loop
	//closes when window is closed
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//tells opengl which shader to use
		//glUseProgram(shaderProgram);
		ourShader.Activate();

		glUniform1f(uniID, 0.0f);

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
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		//updates GLFW
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ourShader.Delete();
	//glDeleteTextures(1, &texture);

	//closes window when program ends
	glfwDestroyWindow(window);
	//closes GLFW
	glfwTerminate();
	return 0;
}