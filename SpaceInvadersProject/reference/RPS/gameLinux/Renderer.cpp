#include"Renderer.h"


void Renderer::Draw(const VertexArray &vArray, const IndexBuffer &iBuffer, const Shader &shader) const{
		shader.Bind();
		vArray.Bind();
		iBuffer.Bind();

		glDrawElements(GL_TRIANGLES, iBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const{
	glClear(GL_COLOR_BUFFER_BIT);
}