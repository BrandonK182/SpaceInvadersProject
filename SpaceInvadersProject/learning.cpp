
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

#include"shaders.h"

const int screenWidth = 1080;
const int screenHeight = 720;

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
	GLfloat verticies[] =
	{
		//positions				//colors				//texture Coordinates
		0.5f, 0.5f, 0.0f,		1.0f,0.0f,0.0f,			1.0f,1.0f,	//top right
		0.5f,-0.5f, 0.0f,		1.0f,0.0f,0.0f,			1.0f,0.0f,	//bottom right
		-0.5f,-0.5f,0.0f,		1.0f,0.0f,0.0f,			0.0f,0.0f,	//bottom left
		-0.5, 0.5f, 0.0f,		1.0f,0.0f,0.0f,			0.0f,1.0f	//top left
	};

	GLuint indices[] =
	{
		0,1,3,		//first triangle
		1,2,3		//second triangle
	};

	//creates window object in 800x800 pixels
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
	//top left corner coordinates (0,0) to bottom right coordinates (800,800)
	glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("core.vs","core.frag");

	//enable textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*no longer needed with new core files
	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//specify that we are using vertex shader, it is on 1 screen, and the source
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//specify that we are using fragment shader, it is on 1 screen, and the source
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	*/

	//virtual buffer object
	GLuint VAO,		//attributes
		VBO,		//buffer
		EBO;		//index bugger

	//generate objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//binds VAO so it is usable
	glBindVertexArray(VAO);

	//bind VBO specifying it is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//store verticies in buffer
	//buffer, size of data, data, use of data
	//gl_stream, modified once
	//gl_static, modified once and used many times
	//gl_dynamic, modified many times
	//DRAW draws on the screen
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	//drawing with indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//work to knows how to read the VAO
	//vertex attribute, communicate with vertex shader from outside
	//1)position of vertext attribute
	//2)how many values of vertex
	//3)what kind of value
	//4)if using integers
	//5)amount of data (3 float values)
	//6)offset (no offset as verticies are at beggining of array)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//binds both to 0 so we don't modify data we don't want
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//clears buffer color and prepares another color in buffer
	//navy blue color 0.07f, 0.13f, 0.17f
	//transparency 1.0f
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//execute color command on color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//changes to the buffer
	glfwSwapBuffers(window);


	//Textures
	GLuint texture;
	int widthImg, heightImg;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image = SOIL_load_image("zoro.png", &widthImg, &heightImg, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Main while loop
	//closes when window is closed
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//tells opengl which shader to use
		//glUseProgram(shaderProgram);
		ourShader.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);

		glBindVertexArray(VAO);

		//draws triangle 
		//glDrawArrays(GL_TRIANGLES, 0, 3); //replaced with next line
		//data, number of indicies, datatype, index
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		//updates GLFW
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	//closes window when program ends
	glfwDestroyWindow(window);
	//closes GLFW
	glfwTerminate();
	return 0;
}
