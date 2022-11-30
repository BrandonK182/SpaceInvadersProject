#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	//bind VBO specifying it is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	//bind VBO specifying it is an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}