#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray(){
	glGenVertexArrays(1, &id);

}

VertexArray::~VertexArray(){
	glDeleteVertexArrays(1, &id);
}

void VertexArray::addBuffer(const VertexBuffer &vBuffer, const VertexBufferLayout &layout){
	Bind();
	vBuffer.Bind();
	const auto &elements = layout.GetElements();
	long long unsigned int offset = 0;
	for(unsigned int i = 0; i < elements.size(); i++){
		const auto &element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.i, element.type, element.normal, layout.GetStride(), (const void*)offset);
		offset += element.i * VertexBufferElement::sizeofType(element.type);
	}
}

void VertexArray::Bind() const{
	glBindVertexArray(id);
}

void VertexArray::unBind() const{
	glBindVertexArray(0);
}