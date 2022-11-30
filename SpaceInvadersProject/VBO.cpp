#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	//bind VBO specifying it is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//store verticies in buffer
	//buffer, size of data, data, use of data
	//gl_stream, modified once
	//gl_static, modified once and used many times
	//gl_dynamic, modified many times
	//DRAW draws on the screen
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	//bind VBO specifying it is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	//bind VBO specifying it is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
